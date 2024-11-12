//  78% 自作の数値クラスで演算をムーブに対応する方法
/*
window.addEventListener("scroll", () => {
  const scrollTop = window.scrollY;
  const documentHeight = document.documentElement.scrollHeight - window.innerHeight;
  const scrollPercentage = (scrollTop / documentHeight) * 100;
  console.log(`スクロール位置: ${Math.round(scrollPercentage)}%`);
});
*/

struct Point{
    int x,y,z;
    Point() : x(0), y(0), z(0) {}
    Point(int x, int y, int z) : x(x), y(y), z(z) {}
    Point(const Point & r)
        :x(r.x),y(r.y),z(r.z)
    {}
    Point & operator=(const Point & r){
        x=r.x;
        y=r.y;
        z=r.z;
        return *this;
    }
};
template<typename T>
class dynamic_array{
    private:
        T* first;
        T * last;
    public:
        dynamic_array(std::size_t size=0)
            :first(new T[size]),last(first +size)
            {}
        ~dynamic_array()
        {
            delete [] first;
        }
        T &operator [](std::size_t i) const noexcept{
            return first[i];
        }
        std::size_t size() const noexcept{
            return last- first;
        }
        T * begin() const noexcept{
            return first;
        }
        T * end() const noexcept{
            return last;
        }
        
        dynamic_array(dynamic_array &r)
            :first(new T[r.size()]),last (first + r.size())
            {
                r.first=nullptr;
                r.last=nullptr;
            }
        dynamic_array & operator =(const dynamic_array & r){
            if(this !=&r && size()!=r.size()){
                delete  first;
                first = new T[r.size()];
                last= first + r.size();
                std::copy(r.begin(),r.end(),begin());
            }
        }
        dynamic_array(dynamic_array && r)
            :first(r.first),last(r.last)
            {
                r.first=nullptr;
                r.last=nullptr;
            }
        dynamic_array & operator =(dynamic_array && r){
            delete first;
            first=r.first;
            last=r.last;
            r.first=nullptr;
            r.last=nullptr;
            return *this;
        }
};
// lvalue reference
template <typename T>
T && move(T && t) noexcept{
    return static_cast<T && >(t);
}

template<typename T>
std::remove_reference_t<T> && move(T && t) noexcept{
    return static_cast<std::remove_reference_t<T>&&>(t);
}
template<class T>
constexpr T && forward(std::remove_reference_t<T> & t) noexcept{
    return static_cast<T&&>(t);
}
template<class T>
constexpr T && forward(std::remove_reference_t<T>&& t) noexcept{
    return static_cast<T&&>(t);
}
template<typename T>
class unique_ptr{
    T* ptr=nullptr;
public:
    unique_ptr(){
    }
    explicit unique_ptr(T * ptr)
        :ptr(ptr)
        {}
    ~unique_ptr(){
        delete ptr;
    }
    
    unique_ptr(const unique_ptr & r)=delete;
    unique_ptr & operator =(const unique_ptr & r)=delete;

    unique_ptr(unique_ptr && r)
        :ptr(r.ptr)
        {
            r.ptr=nullptr;
        }
    unique_ptr & operator=(unique_ptr && r){
        delete ptr;
        ptr=r.ptr;
        r.ptr=nullptr;
    }
    T & operator *() noexcept{
        return *ptr;
    }
    T * operator ->() noexcept{
        return ptr;
    }
    T * get() noexcept{
        return ptr;
    }
};
template<typename T>
class shared_ptr{
    T *ptr;
    std::size_t *count;
    void release(){
        if(count ==nullptr)
            return;
        --*count;
        if(*count==0){
            delete ptr;
            ptr=nullptr;
            delete count;
            count=nullptr;
        }
    }
public:
    shared_ptr(){}
    explicit shared_ptr(T *ptr)
        :ptr(ptr),count(new std::size_t(1))
        {}
    shared_ptr(const shared_ptr & r)
        :ptr(r.ptr),count(r.count)
        {
            ++*count;
        }
    ~shared_ptr(){
        release();
    }
    shared_ptr & operator =(const shared_ptr & r){
        if(this ==&r)
            return *this;
        release();
        ptr=r.ptr;
        count =r.count;
        ++*count;
    }
    shared_ptr (shared_ptr && r)
        :ptr(r.ptr),count(r.count)
        {
            r.ptr=nullptr;
            r.count=nullptr;
        }
    shared_ptr & operator= (shared_ptr && r){
        release();
        ptr=r.ptr;
        count=r.count;
        r.ptr=nullptr;
        r.count=nullptr;
    }
    T & operator *()noexcept{
        return *ptr;
    }
    T * operator->() noexcept{
        return ptr;
    }
    T * get( ) noexcept{
        return ptr;
    }
};
std::shared_ptr<int>last_ptr;
bool is_equal_to_last_ptr(std::shared_ptr<int>ptr){
    if(last_ptr==nullptr)
        last_ptr=ptr;
    bool b=*last_ptr==*ptr;
    last_ptr=ptr;
    return b;
}
int main() {
    auto p1=std::make_shared<int>(1);
    auto p2=std::make_shared<int>(2);

    std::cout<<is_equal_to_last_ptr(p1);
    std::cout<<is_equal_to_last_ptr(p2);
    *p2=1;
    std::cout<<is_equal_to_last_ptr(p1);

}
