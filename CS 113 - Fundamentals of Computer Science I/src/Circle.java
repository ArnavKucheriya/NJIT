public class Circle {
    private Point center;
    private int radius;

    public Circle(Point center, int radius) {
        this.center = center;
        this.radius = radius;
    }

    // Getters
    public Point getCenter() {
        return center;
    }

    public int getRadius() {
        return radius;
    }

    // Setters
    public void setCenter(Point center) {
        this.center = center;
    }

    public void setRadius(int radius) {
        this.radius = radius;
    }

    // Equals method
    public boolean equals(Circle other) {
        return this.radius == other.radius;
    }

    // Circumference method
    public double circumference() {
        return 2 * Math.PI * radius;
    }

    // toString method
    public String toString() {
        return "Circle with radius " + radius + ", center " + center.toString();
    }
}
