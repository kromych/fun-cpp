/*
	How many ways of making change for N cents given an infinite supply of coins {C} = { c_i : i: 0..n-1 } 
	there are?

	The example below is for N = 10 and {C} = {2,5,3,6}.
*/

template <int N>
struct coins_t
{
	static constexpr int value = 0;	
};

template <>
struct coins_t<0>
{
	static constexpr int value = 2;	
};

template <>
struct coins_t<1>
{
	static constexpr int value = 5;	
};

template <>
struct coins_t<2>
{
	static constexpr int value = 3;	
};

template <>
struct coins_t<3>
{
	static constexpr int value = 6;	
};


constexpr auto coin_change_max_index = 3;
constexpr auto money_to_change = 10;

template <
	bool p_coin_index_geq_0 = true, 
	bool p_money_geq_0 = true, 
	int money = money_to_change, 
	int coin_index = coin_change_max_index> 
struct coin_change_t
{
	static constexpr int value = 
			coin_change_t<
					// Predicates
					(coin_index - 1 >= 0), 
					(money >= 0),
					// Values
					(money), 
					(coin_index - 1) 
				>::value

			+

			coin_change_t<
					// Predicates
					(coin_index >= 0), 
					(money - coins_t<coin_index>::value >= 0),
					// Values
					(money - coins_t<coin_index>::value), 
					(coin_index)
				>::value;
};

template <bool p_money_geq_0, int money, int coin_index> 
struct coin_change_t<false, p_money_geq_0, money, coin_index>
{
	// Ran ouf of coins values to try

	static constexpr int value = 0;
};

template <int money, int coin_index> 
struct coin_change_t<true, false, money, coin_index> 
{
	// Ran ouf of money when changing

	static constexpr int value = 0;
};

template <int coin_index> 
struct coin_change_t<true, true, 0, coin_index> 
{
	// Just enough to change: +1 way!

	static constexpr int value = 1;
};

int main()
{
	return coin_change_t<>::value;
}
