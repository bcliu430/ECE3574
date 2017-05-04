// Here I am using Qt just to get keypresses directly
#include <QApplication>
#include <QWidget>
#include <QKeyEvent>
#include <QDebug>
#include <iostream>

// this would be defined in a header
#include <cstdint>
namespace embed
{
    // allow up to 255 characters
    template<typename T, std::uint8_t N>
    class string_buffer
    {
    public:
	string_buffer(): top(0) {};
		
	bool empty(){
	    return (top == 0);
	}
    
	bool push(const T& value){
	    if(top >= N) return false;
	    
	    data[top] = value;
	    ++top;

	    return true;
	}
    
	bool pop(){
	    if(top == 0) return false;
	    --top;
	    return true;
	}
    
	bool at(std::uint8_t index, T& value){
	    if(index >= top) return false;
	    value = data[index];
	    return true;
	}
	
	std::uint8_t size(){
	    return top;
	}
	
	void clear(){
	    top = 0;
	}
	
    private:
	T data[N];
	long int top;
    };
}

// this is just an easy way to get keyboard events
// this would be typically be replaced by a polled
// sampling of row/column pins with debouncing on an MCU
class EntryReader: public QWidget
{
    Q_OBJECT

    bool eventFilter(QObject *Object, QEvent *event){
	
	if (event->type() == QEvent::KeyPress){
	    QKeyEvent *keyEvent = (QKeyEvent*)event;
		
	    char value =  keyEvent->text().at(0).toAscii();

	    qDebug() << "Key Press Decoded to: " << (int) value << " " << value;

	    switch(value){
	    case BACKSPACE:
		entries.pop();
		break;
	    case ENTER:
		for(std::uint8_t i = 0; i < entries.size(); ++i){
		    // just for demonstration
		    char c;
		    if(entries.at(i, c)) std::cout << c;
		}
		std::cout << std::endl;
		
		entries.clear();
		break;
	    default:
		entries.push(value);
	    };
	    
	    return true;
	}
	return false;
    }
    static const char BACKSPACE = 8;
    static const char ENTER = 13;
    
    static const std::uint8_t BUFFER_SIZE = 100;
    embed::string_buffer<char, BUFFER_SIZE> entries;
};

#include "main.moc"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    EntryReader er;

    app.installEventFilter(&er);    

    er.show();
    app.exec();
  
    return 0;
}
