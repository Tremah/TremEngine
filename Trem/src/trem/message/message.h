#pragma once

//c++ includes

//external library includes

//game engine includes




namespace Trem
{
  struct MsgTypes
  {
    using Type = uint16_t;
    enum : Type
    {
      NullMessage = 0,
      GamePaused, GameResumed, GameClosed, 
      KeyPressed, KeyRepeated, KeyReleased,
      MouseMoved, LMouseButtonPressed, RMouseButtonPressed,
      WindowResized, WindowMinimized, WindowClosed
    };        
    static Type count() { return 13; }

    static std::string toString(Type type);
    private:
      //prevent implicit cast to any integral type
      template<typename T> operator T() const;
  };
  using MsgType = MsgTypes::Type;

  struct MsgCategories
  {
    using Type = uint16_t;
    using Category = Type;
    enum : Type
    {
      NullCategory  = 0, 
      Event         = BIT(1),
      GameEvent     = BIT(2),  
      InputEvent    = BIT(3),
      KeyboardEvent = BIT(4),
      MouseEvent    = BIT(5),
      WindowEvent   = BIT(6)
    };        
    static Type count() { return 7; }

    static std::string toString(Category type);
    private:
      //prevent implicit cast to any integral type
      template<typename T> operator T() const;
  };
  using MsgCategory = MsgCategories::Type;

  /**
    *  \brief Base class for message system.
    *
    */
  class Message
  {
    public:      
      //Constructors and deconstructors 
      Message(const Message&) = default;
      Message(Message&&) = default;
      Message& operator=(const Message&) = default;
      Message& operator=(Message&&) = default; 
      virtual ~Message() { std::cout << "msg deconstructed" << std::endl;}

      Message() : handled_{false}, type_{MsgTypes::NullMessage}, category_{MsgCategories::NullCategory}  {}
      Message(const MsgType type, const MsgCategory category) : handled_{false}, type_{type}, category_{category} {}

      //Member variables
      bool handled_;

      //Member functions
      MsgCategory category() const; 
      MsgType type()         const;
      bool inCategory(MsgCategory category);

      virtual std::string toString() const;     

    protected:
      //Constructors and deconstructors

      //Member variables
      MsgType     type_;
      MsgCategory category_;

      //Member functions

    private:
      //Member variables

      //Member functions      
  };  

  //--------------------------
  // Typenames for ease of use
  //--------------------------
  
  /**
   * \brief Callback to queue a message.<br>
   *        Receiving function is taking ownership to store the unique pointer
   */
  using MsgQueueCallback = std::function<void(UnqPtr<Message>&&)>;

  /**
   * \brief Callback to dispatch (process) a message
   *        Receving function won't (can't) take ownership, is only accessing the pointer
   */
  using MsgDispatchCallback = std::function<bool(const UnqPtr<Message>&)>;
}
