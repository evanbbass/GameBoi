[Back to Home](../../README.md)

[Back to Week 4](Week4.md)

[Next to Week 6](Week6.md)

## 6/28/2017

Due to other commitments, this week's tasks weren't fully completed. I completed the CPU refactor to support interrupts and added timers to fire interrtups, but almost no work was done on the GPU. As this was all backend work, there isn't much to show.

One thing I did to improve the debugger was wrap all of the C++/CLI calls to unmanaged code in a try-catch. This lets me get better error messages when something breaks than "An unmanaged component has thrown an exception."

```c++
String^ CPUManaged::GetDisassembly(Byte opcode, UInt16 operand)
{
	// old way doesn't handle exceptions, and when something breaks it isn't helpful
	// return gcnew String(CPU::GetDisassembly(opcode, operand).c_str());
    
	// new way catches the exception and wraps it in a managed exception for better debugging
	try
	{
		return gcnew String(CPU::GetDisassembly(opcode, operand).c_str());
	}
	catch (exception& ex)
	{
		throw gcnew Exception(gcnew String(ex.what()));
	}
}
```

This week was also the mid-point update in class. You can see the slides for my presentation [here](../Resources/Update.pptx).
