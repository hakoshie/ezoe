class Integer{
    int *ptr;
public:
    explicit Integer(int value=0)
        :ptr(new int(value)){}
    ~Integer(){
        delete ptr;
    }

    Integer(const Integer & r)
        :ptr(new int(*r.ptr)){}
    Integer& operator =(const Integer & r){
        if(this !=&r)
            *ptr=*r.ptr;
        return *this;
    }
    // move constructor
    Integer(Integer && r)
        :ptr(r.ptr)
        {r.ptr=nullptr;}
    Integer operator =(Integer && r){
        delete ptr;
        ptr=r.ptr;
        r.ptr=nullptr;
        return *this;
    }
    Integer & operator +=(const Integer & r){
        *ptr+=*r.ptr;
        return * this;
    }
    Integer & operator -=(const Integer & r){
        *ptr-=*r.ptr;
        return *this;
    }
    Integer operator -() const &{
        Integer result (-*ptr);
        return result;
    }
    // rvalue
    Integer operator -() &&
    {
        auto result=std::move(*this);
        *result.ptr=-*result.ptr;
        return result;
    }
    Integer operator +(const Integer & r) const &{
        return Integer(*ptr+*r.ptr);
    }
    Integer operator  +(const Integer & r) &&{
        auto result=std::move(*this);
        result+=r;
        return result;
    }
    Integer operator +(Integer && r) const &{
        auto result=std::move(r);
        result+=*this;
        return result;
    }
    Integer operator +(Integer && r) &&{
        return std::move(r)+*this;
    }
    void make_it_negative(){
        *ptr=-*ptr;
    }
};
