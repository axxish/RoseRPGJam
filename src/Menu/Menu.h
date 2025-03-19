#pragma once

class Menu
{
  public:

    Menu(){
      RenderBlocking = true;
      UpdateBlocking = true;
    }

    virtual ~Menu() = default;

    bool RenderBlocking;
    bool UpdateBlocking;


    virtual void OnUpdate(float ts)
    {
    }
    virtual void OnRender()
    {
    }
};
