package MidTerm1_Practice;

public class Project{
    private String title;
    private int pages;

    public Project(String title, int pages){
        this.pages = pages;
        this.title = title;
    }
    public void setTitle(String title){
        this.title = title;
    }
    public int getPages(){
        return this.pages;
    }
    public String getTitle(){
        return this.title;
    }
    public int addPages(int morePages){
        this.pages = this.pages + morePages;
        return this.pages;
    }
    public String toString(){
        return "Project Title: "+this.title+", Number of Pages: "+this.pages;
    }
}
