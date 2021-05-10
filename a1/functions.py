def check_intersection(p1, p2, p3, p4):
    l1 = linear_solver(p1, p2)
    l2 = linear_solver(p3, p4)
    D  = l1[0] * l2[1] - l1[1] * l2[0]
    Dx = l1[2] * l2[1] - l1[1] * l2[2]
    Dy = l1[0] * l2[2] - l1[2] * l2[0]
    if D != 0:
        x = Dx / D
        y = Dy / D
        if check_med(x, y, p1, p2) and check_med(x, y, p3, p4):
            return x,y
    return False

def check_med(x, y, p1, p2):
    if (x <= p1[0]  and x >= p2[0]) or (x >= p1[0]  and x <= p2[0]):
        if (y <= p1[1]  and y >= p2[1]) or (y >= p1[1]  and y <= p2[1]):
            return True
    return False

def linear_solver(p1, p2):
    A = (p1[1] - p2[1])
    B = (p2[0] - p1[0])
    C = (p1[0]*p2[1] - p2[0]*p1[1])
    return A, B, -C

