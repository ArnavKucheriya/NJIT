public class Point{
    private int x, y;

    public Point(int newX, int newY){
        x = newX;
        y = newY;
    }

    public String toString(){
        return "x:"+x+","+"y:"+y;
    }

    public double distance(Point other){
        return Math.sqrt(Math.pow(x-other.x,2)+Math.pow(y-other.y,2));
    }
}

