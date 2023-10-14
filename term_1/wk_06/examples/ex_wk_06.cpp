#include <array>
#include <algorithm>
#include <iostream>

template <class T>
class Euler
{
public:
    typedef typename T::state_type State;
    static typename T::state_type make_step(State& state, const float dt){
        auto f = T::dfdt(state);
        for (auto it = f.state.begin(); it != f.state.end(); ++it) {
           const int index = std::distance(f.state.begin(), it);
           f[index] = state[index] + dt*f[index];
        }
        return f;
    }
};

template <typename MP, int N>
class MyState
{
public:
    std::array<MP, N> state;
    const size_t size() const{
        return state.size();
    }

    MP& operator[](int i) { return state[i]; }

    MyState (const std::array<MP, N>& s){
        std::copy_n(s.begin(), s.size(), state.begin());
    }
// private:
    typedef MP ftype;
    typedef std::array<MP, N> state_type ;
};

template <typename T>
class MyEquation
{
public:   
    static T dfdt(T& s){
        return T (typename T::state_type {s[1], -1*s[0]});
    }
    typedef T state_type ;
};

int main()
{
    MyState<float, 2> init {std::array<float,2>{1.0f, 0.0f}};
    std::cout << "hello" << std::endl;
    auto step = Euler<MyEquation<MyState<float, 2>>>::make_step(init, 0.01);
    std::cout << step[0] << step[1] << std::endl;
    std::swap(step, init);
    step = Euler<MyEquation<MyState<float, 2>>>::make_step(init, 0.01);
    std::cout << step[0] << step[1] << std::endl;
    return 0;
}