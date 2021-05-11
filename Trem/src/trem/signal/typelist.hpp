#pragma once

namespace Trem::tl
{
  template <typename... Ts>
  struct TypeList {};

  //get first entry of the type list
  template <typename L>
  struct front;

  template <typename Head, typename... Tail>
  struct front<TypeList<Head, Tail...>>
  {
    using type = Head;
  };

  template <typename L>
  struct back;

  //get last entry of the type list
  template <typename... Ts>
  struct back<TypeList<Ts...>>
  {
    template <typename T>
    struct tag
    {
      using type = T;
    };

    using type = typename decltype((tag<Ts>{}, ...))::type;
  };

  //Get length of the type list
  template <typename... Ts>
  struct length;

  template <typename... Ts>
  struct length<TypeList<Ts...>>
  {
    inline static constexpr std::size_t value = sizeof...(Ts);
  };

  //Get type at position
  template <int index, typename L>
  struct typeAt;

  template <int index, typename H, typename... T>
  struct typeAt<index, TypeList<H, T...>>
  {
    static_assert(index - 1 < sizeof...(T), "Index for type list is out of bounds!");
    using type = typename typeAt<index - 1, TypeList<T...>>::type;

  };

  template <typename H, typename... T>
  struct typeAt<0, TypeList<H, T...>>
  {
    using type = H;
  };

  template <typename Q, typename T>
  struct indexOf;

  template <typename Q, typename T>
  struct indexOf<Q, TypeList<T>>
  {
    inline static constexpr int32_t value = -1;
  };

  template <typename Q, typename... Ts>
  struct indexOf<Q, TypeList<Q, Ts...>>
  {
    inline static constexpr int32_t value = 1;
  };

  template <typename Q, typename H, typename... T>
  struct indexOf<Q, TypeList<H, T...>>
  {
    inline static constexpr int32_t value = indexOf<Q, TypeList<T...>>::value == -1 ? -1 : 1 + indexOf<Q, TypeList<T...>>::value;
  };

  template <typename Q, typename L>
  struct contains;

  template <typename Q, typename T>
  struct contains<Q, TypeList<T>>
  {
    inline static constexpr bool value = false;
  };

  template <typename Q>
  struct contains<Q, TypeList<Q>>
  {
    inline static constexpr bool value = true;
  };

  template <typename Q, typename... Ts>
  struct contains<Q, TypeList<Q, Ts...>>
  {
    inline static constexpr bool value = true;
  };

  template <typename Q, typename T, typename... Ts>
  struct contains<Q, TypeList<T, Ts...>>
  {
    inline static constexpr bool value = contains<Q, TypeList<Ts...>>::value;
  };

  template <typename A, typename L>
  struct append;

  template <typename A, typename... Ts>
  struct append<A, TypeList<Ts...>>
  {
    using type = typename TypeList<Ts..., A>;
  };

  template <typename P, typename L>
  struct prepend;

  template <typename P, typename... Ts>
  struct prepend<P, TypeList<Ts...>>
  {
    using type = typename TypeList<P, Ts...>;
  };

  template <typename R, typename L>
  struct remove;

  template <typename R, typename... T>
  struct remove<R, TypeList<R, T...>>
  {
    using type = TypeList<T...>;
  };

  template <typename R, typename H, typename... T>
  struct remove<R, TypeList<H, T...>>
  {
    using type = typename remove<R, TypeList<T...>>::type;
  };

  template <typename LL, typename RL>
  struct compareTL;

  template <typename... TR>
  struct compareTL<TypeList<>, TypeList<TR...>>
  {
    inline static constexpr bool value = false;
  };

  template <typename HL, typename... TL, typename... TR> 
  struct compareTL<TypeList<HL, TL...>, TypeList<TR...>>
  {
    private:
      inline static constexpr bool temp = contains<HL, TypeList<TR...>>::value;

    public:
      inline static constexpr bool value = temp == false ? false : compareTL<TypeList<TL...>, TypeList<TR...>>::value;
  };
}