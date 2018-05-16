# Lamda表达式

```
Lamda 表达式
To create a lambda expression, you specify input parameters (if any) on the left side of the lambda operator =>,
and you put the expression or statement block on the other side. For example, the lambda expression x => x * x 
specifies a parameter that’s named x and returns the value of x squared. You can assign this expression to a 
delegate type, as the following example shows:
delegate int del(int i);  
static void Main(string[] args)  
{  
    del myDelegate = x => x * x;  
    int j = myDelegate(5); //j = 25  
}
public bool FloatTopLayer
{
    get => ForwardParameters.GetParameterValue<bool>(CalculationParameters.Names.JxRA_FLOAT_TOP_LAYER, true);
    set => ForwardParameters.SetParameterValue<bool>(CalculationParameters.Names.JxRA_FLOAT_TOP_LAYER, value);
}
```



