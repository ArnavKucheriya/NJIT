class Book {
    // Instance data
    private String title;
    private int pages;

    // Default constructor
    public Book() {
        this.title = "Java Programming";
        this.pages = 200;
    }

    // Getter methods
    public String getTitle() {
        return title;
    }

    public int getPages() {
        return pages;
    }

    // Setter methods
    public void setTitle(String title) {
        this.title = title;
    }

    public void setPages(int pages) {
        this.pages = pages;
    }

    public String toString() {
        return "Title: " + title + ", Pages: " + pages;
    }
}

