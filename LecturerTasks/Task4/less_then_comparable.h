template <typename T>
class less_than_comparable {
public:
    bool operator>(const T& rhs) const {
        return rhs < static_cast<const T&>(*this);
    }

    bool operator<=(const T& rhs) const {
        return !(static_cast<const T&>(*this) > rhs);
    }

    bool operator>=(const T& rhs) const {
        return !(static_cast<const T&>(*this) < rhs);
    }

    bool operator==(const T& rhs) const {
        return !(rhs > static_cast<const T&>(*this)) 
            && !(rhs < static_cast<const T&>(*this));
    }

    bool operator!=(const T& rhs) const {
        return !(rhs == static_cast<const T&>(*this));
    }
};