#pragma once

//c++ includes

//external library includes

//custom (own) library includes

//game engine includes

namespace Trem
{  
  using KeyCode = uint16_t;
  using MouseCode = uint16_t;
}

/**
 *  \brief Enumeration to represent keyboard codes
 *
 */
namespace Trem::Key
{
  enum : KeyCode
  {
    //Special characters
    Space       = 32,
    Apostrophe  = 39, /* ' */
    Comma       = 44, /* , */
    Minus       = 45, /* - */
    Period      = 46, /* . */
    Slash       = 47, /* / */

    //Keyboard num keys
    K0          = 48,
    K1          = 49,
    K2          = 50,
    K3          = 51,
    K4          = 52,
    K5          = 53,
    K6          = 54,
    K7          = 55,
    K8          = 56,
    K9          = 57,

    //Special characters
    Semicolon   = 59, /* ; */
    Equal       = 61, /* = */

    //Alphabet
    A           = 65,
    B           = 66,
    C           = 67,
    D           = 68,
    E           = 69,
    F           = 70,
    G           = 71,
    H           = 72,
    I           = 73,
    J           = 74,
    K           = 75,
    L           = 76,
    M           = 77,
    N           = 78,
    O           = 79,
    P           = 80,
    Q           = 81,
    R           = 82,
    S           = 83,
    T           = 84,
    U           = 85,
    V           = 86,
    W           = 87,
    X           = 88,
    Y           = 89,
    Z           = 90,

    //Special characters
    LeftBracket = 91, /* [ */
    BackSlash   = 92, /* \ */
    RightBracket= 93, /* ] */
    GraveAccent = 96, /* ` */

    //Non-US
    World1      = 161,
    World2      = 162,

    //Function Keys
    Escape      = 256,
    Enter       = 257,
    Tab         = 258,
    Backspace   = 259,
    Insert      = 260,
    Delete      = 261,
    Right       = 262,
    Left        = 263,
    Down        = 264,
    Up          = 265,
    PageUp      = 266,
    PageDown    = 267,
    Home        = 268,
    End         = 269,
    CapsLock    = 280,
    ScrollLock  = 281,
    NumLock     = 282,
    PrintScreen = 283,
    Pause       = 284,
    F1          = 290,
    F2          = 291,
    F3          = 292,
    F4          = 293,
    F5          = 294,
    F6          = 295,
    F7          = 296,
    F8          = 297,
    F9          = 298,
    F10         = 299,
    F11         = 300,
    F12         = 301,
    F13         = 302,
    F14         = 303,
    F15         = 304,
    F16         = 305,
    F17         = 306,
    F18         = 307,
    F19         = 308,
    F20         = 309,
    F21         = 310,
    F22         = 311,
    F23         = 312,
    F24         = 313,
    F25         = 314,

    //Numpad
    N0          = 320,
    N1          = 321,
    N2          = 322,
    N3          = 323,
    N4          = 324,
    N5          = 325,
    N6          = 326,
    N7          = 327,
    N8          = 328,
    N9          = 329,
    NComma      = 330,
    NDivide     = 331,
    NMultiply   = 332,
    NSubtract   = 333,
    NAdd        = 334,
    NEnter      = 335,
    NEqual      = 336,
    LShift      = 340,
    LControl    = 341,
    LAlt        = 342,
    LSuper      = 343,
    RShift      = 344,
    RControl    = 345,
    RAlt        = 346,
    RSuper      = 347,
    Menu        = 348
  };
}

/**
 *  \brief Enumeration to represent mouse codes
 *
 */
namespace Trem::Mouse
{
  enum : MouseCode
  {
    Button1       = 0,
    Button2       = 1,
    Button3       = 2,
    Button4       = 3,
    Button5       = 4,
    Button6       = 5,
    Button7       = 6,
    Button8       = 7,
    ButtonLast    = Button8,
    ButtonLeft    = Button1,
    ButtonRight   = Button2,
    ButtonMiddle  = Button3
  };
}
