#ifndef BOOK_H
#define BOOK_H

typedef int PageNumberType;

class book{

public:
    Coverage getCoverage();

    ContentTableType getContents();

    void getPage(PageNumberType page);

    PageNumberType getCurrentPage(); // get current page

}

#endif
