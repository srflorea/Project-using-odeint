#include <boost/numeric/odeint.hpp>
#include <boost/numeric/interval.hpp>

#include <iostream>
#include <vector>

using namespace std;
using namespace boost::numeric::odeint;
using namespace boost::numeric;
using namespace interval_lib;

// The type of container used to hold the state vector.
typedef vector< interval<double> > state_type;

//The rhs of x' = f(x)
void simple_ode(const state_type &x, state_type &dxdt, const double)
{
	dxdt[0] = -x[0];
}

//observer that will store the intermediate steps in a container
struct push_back_state_and_time
{
    push_back_state_and_time() { }

    void operator()( const state_type &x , double t )
    {
        double low  = x[0].lower();
        double up   = x[0].upper();

        cout << t << '\t' << low << '\t' << up << '\n';
    }
};

int main()
{
    //initialization of state
	state_type start_state(1);
	interval<double> initial_interval(100, 100.1);
    start_state[0] = initial_interval;

    //initialization of integrating function parameters
    double start_time(0.0), dt(0.01);
    int num_of_steps(500);

    //initialization of numerical stepper that will be used for numerical integration
	runge_kutta4< state_type > stepper;
	integrate_n_steps(stepper, simple_ode, start_state, start_time, dt, num_of_steps, 
            push_back_state_and_time()) ;

	return 0;
}