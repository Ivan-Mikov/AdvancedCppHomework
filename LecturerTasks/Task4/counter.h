template <typename T>
class counter {
    // inline позволяет определить статическую переменную
    static inline unsigned int _count = 0;
public:
    counter() {
        _count++;
    }

    ~counter() {
        _count--;
    }

    static unsigned int count() {
        return _count;
    }
};