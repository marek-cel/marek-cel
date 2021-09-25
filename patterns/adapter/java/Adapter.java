package pl.marekcel.dev.cel.patterns.java.adapter;

public class Adapter 
    implements WhatIWant
{
    private WhatIHave mWhatIHave = new WhatIHave();
    
    @Override
    public void f()
    {
        mWhatIHave.h();
        mWhatIHave.g();
    }
}
