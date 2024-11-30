//  99% 関数から抜けるまで実行(finish)
/*
window.addEventListener("scroll", () => {
  const scrollTop = window.scrollY;
  const documentHeight = document.documentElement.scrollHeight - window.innerHeight;
  const scrollPercentage = (scrollTop / documentHeight) * 100;
  console.log(`スクロール位置: ${Math.round(scrollPercentage)}%`);
});
*/
#include <iostream>
#include <string>
void f(){}
void apple(){
  f();
}
void banana(){
  f();
}
void cherry(){
  apple();
}
void hello(){
  std::cout << "Hello, World!" << std::endl;
}
int main(){
  int x{};
  std::cin>>x;
  std::cout<<1/x;

}
