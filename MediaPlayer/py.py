import sys
import math
import cv2 as cv
import numpy as np

def auto_canny(gray, sigma=0.33):
    """Détection automatique des bords avec Canny."""
    v = np.median(gray)
    lower = int(max(0, (1.0 - sigma) * v))
    upper = int(min(255, (1.0 + sigma) * v))
    return cv.Canny(gray, lower, upper)

def niveau(image, eps=np.deg2rad(10)):
    """Détection des lignes horizontales et calcul de l’angle moyen."""
    
    # Conversion en niveaux de gris + flou pour réduire le bruit
    gray = cv.cvtColor(image, cv.COLOR_BGR2GRAY)
    blurred = cv.GaussianBlur(gray, (3, 3), 0)

    edges = auto_canny(blurred)

    # Détection des lignes avec la transformée de Hough
    lines = cv.HoughLines(edges, 1, np.pi / 180, 120)  # Seuil réduit pour plus de détection
    valid_thetas = []

    if lines is not None:
        for line in lines:
            rho, theta = line[0]
            if abs(theta - np.pi/2) < eps:  # On garde les lignes proches de l'horizontale
                valid_thetas.append(theta)

    # Calcul de l'angle moyen des lignes horizontales détectées
    theta_mean = None
    if valid_thetas:
        sum_sin = sum(math.sin(t) for t in valid_thetas)
        sum_cos = sum(math.cos(t) for t in valid_thetas)
        theta_mean = math.atan2(sum_sin, sum_cos)
    
    return theta_mean, edges  # Retourne l’angle moyen et l’image segmentée

# Initialisation de la capture vidéo
cap = cv.VideoCapture(1)
if not cap.isOpened():
    print("Erreur : Impossible d'ouvrir la webcam")
    sys.exit()

filtered_angle = None
alpha = 0.5  # Lissage plus réactif

while True:
    ret, frame = cap.read()
    if not ret:
        print("Erreur lors de la lecture de la vidéo")
        break

    # Récupération de l'angle moyen des lignes détectées
    theta_mean, seg = niveau(frame)

    # Lissage de l'angle
    if theta_mean is not None:
        if filtered_angle is None:
            filtered_angle = theta_mean
        else:
            filtered_angle = alpha * theta_mean + (1 - alpha) * filtered_angle
    else:
        if filtered_angle is None:
            filtered_angle = np.pi / 2  # Par défaut, horizontal

    # Conversion en degrés pour choisir la couleur
    angle_degrees = filtered_angle * 180 / np.pi
    tolerance = 3  # Tolérance réduite pour mieux voir les changements

    # Choix de la couleur :
    if angle_degrees > 93:
        color = (0, 0, 255)   # Rouge (incliné vers le haut)
    elif angle_degrees < 87:
        color = (255, 0, 0)   # Bleu (incliné vers le bas)
    else:
        color = (0, 255, 0)   # Vert (horizontale)

    h, w = frame.shape[:2]
    cx, cy = w // 2, h // 2
    L = 1000<  # Longueur de la ligne
    dx = math.sin(filtered_angle)
    dy = -math.cos(filtered_angle)
    pt1 = (int(cx - L * dx), int(cy - L * dy))
    pt2 = (int(cx + L * dx), int(cy + L * dy))
    cv.line(frame, pt1, pt2, color, 3, cv.LINE_AA)

    cv.putText(frame, f"Angle: {angle_degrees:.2f} deg", (10, 30), cv.FONT_HERSHEY_SIMPLEX, 0.8, (0, 255, 255), 2)

    cv.imshow("Ligne Moyenne", frame)
    cv.imshow("Contours (Canny)", seg)

    if cv.waitKey(1) & 0xFF == ord('q'):
        break

cap.release()
cv.destroyAllWindows()
