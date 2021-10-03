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
