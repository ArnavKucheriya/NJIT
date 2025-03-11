package MidTerm1_Practice;
public class Student {
private String name;
private GPA gpa;
public Student(String name, GPA gpa){
    this.name = name;
    this.gpa = gpa;
}
    public GPA getGpa(){
        return gpa;
    }
    public void setName(String name){
        this.name = name;
    }
    public boolean honorRoll(GPA minGpa) {
        return gpa.compareTo(minGpa) >= 0;
    }
    public String toString() {
        return name + ": " + gpa.toString();
    }
}
