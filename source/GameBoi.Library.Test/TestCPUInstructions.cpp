#include "pch.h"
#include "CppUnitTest.h"
#include "CPU.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;
using namespace GameBoi;

namespace GameBoiLibraryTest
{
	TEST_CLASS(TestCPUInstructions)
	{
	public:

		TEST_METHOD(TestCPUInstructions_LD_nn_n)
		{
			MemoryMap memory;
			CPU cpu(memory);
			Registers& registers = cpu.GetRegisters();

			registers.Reset();
			Assert::IsTrue(registers.A == 0u);
			Assert::IsTrue(registers.B == 0u);
			Assert::IsTrue(registers.C == 0u);
			Assert::IsTrue(registers.D == 0u);
			Assert::IsTrue(registers.E == 0u);
			Assert::IsTrue(registers.H == 0u);
			Assert::IsTrue(registers.L == 0u);

			uint8_t value = 0xAB;
			cpu.LD_B_n(value);
			cpu.LD_C_n(value);
			cpu.LD_D_n(value);
			cpu.LD_E_n(value);
			cpu.LD_H_n(value);
			cpu.LD_L_n(value);
			Assert::IsTrue(registers.B == value);
			Assert::IsTrue(registers.C == value);
			Assert::IsTrue(registers.D == value);
			Assert::IsTrue(registers.E == value);
			Assert::IsTrue(registers.H == value);
			Assert::IsTrue(registers.L == value);
		}

		TEST_METHOD(TestCPUInstructions_LD_r1_r2)
		{
			MemoryMap memory;
			CPU cpu(memory);
			Registers& registers = cpu.GetRegisters();

			registers.Reset();
			Assert::IsTrue(registers.A == 0u);
			Assert::IsTrue(registers.B == 0u);
			Assert::IsTrue(registers.C == 0u);
			Assert::IsTrue(registers.D == 0u);
			Assert::IsTrue(registers.E == 0u);
			Assert::IsTrue(registers.H == 0u);
			Assert::IsTrue(registers.L == 0u);

			uint8_t value = 0xAB;
			uint16_t wramAddress = 0xD000;

			registers.A = value;
			cpu.LD_A_A(0);
			cpu.LD_B_A(0);
			cpu.LD_C_A(0);
			cpu.LD_D_A(0);
			cpu.LD_E_A(0);
			cpu.LD_H_A(0);
			cpu.LD_L_A(0);
			Assert::IsTrue(registers.B == value);
			Assert::IsTrue(registers.C == value);
			Assert::IsTrue(registers.D == value);
			Assert::IsTrue(registers.E == value);
			Assert::IsTrue(registers.H == value);
			Assert::IsTrue(registers.L == value);
			registers.Reset();

			registers.B = value;
			cpu.LD_A_B(0);
			cpu.LD_B_B(0);
			cpu.LD_C_B(0);
			cpu.LD_D_B(0);
			cpu.LD_E_B(0);
			cpu.LD_H_B(0);
			cpu.LD_L_B(0);
			Assert::IsTrue(registers.B == value);
			Assert::IsTrue(registers.C == value);
			Assert::IsTrue(registers.D == value);
			Assert::IsTrue(registers.E == value);
			Assert::IsTrue(registers.H == value);
			Assert::IsTrue(registers.L == value);
			registers.Reset();

			registers.C = value;
			cpu.LD_A_C(0);
			cpu.LD_B_C(0);
			cpu.LD_C_C(0);
			cpu.LD_D_C(0);
			cpu.LD_E_C(0);
			cpu.LD_H_C(0);
			cpu.LD_L_C(0);
			Assert::IsTrue(registers.B == value);
			Assert::IsTrue(registers.C == value);
			Assert::IsTrue(registers.D == value);
			Assert::IsTrue(registers.E == value);
			Assert::IsTrue(registers.H == value);
			Assert::IsTrue(registers.L == value);
			registers.Reset();

			registers.D = value;
			cpu.LD_A_D(0);
			cpu.LD_B_D(0);
			cpu.LD_C_D(0);
			cpu.LD_D_D(0);
			cpu.LD_E_D(0);
			cpu.LD_H_D(0);
			cpu.LD_L_D(0);
			Assert::IsTrue(registers.B == value);
			Assert::IsTrue(registers.C == value);
			Assert::IsTrue(registers.D == value);
			Assert::IsTrue(registers.E == value);
			Assert::IsTrue(registers.H == value);
			Assert::IsTrue(registers.L == value);
			registers.Reset();

			registers.E = value;
			cpu.LD_A_E(0);
			cpu.LD_B_E(0);
			cpu.LD_C_E(0);
			cpu.LD_D_E(0);
			cpu.LD_E_E(0);
			cpu.LD_H_E(0);
			cpu.LD_L_E(0);
			Assert::IsTrue(registers.B == value);
			Assert::IsTrue(registers.C == value);
			Assert::IsTrue(registers.D == value);
			Assert::IsTrue(registers.E == value);
			Assert::IsTrue(registers.H == value);
			Assert::IsTrue(registers.L == value);
			registers.Reset();

			registers.H = value;
			cpu.LD_A_H(0);
			cpu.LD_B_H(0);
			cpu.LD_C_H(0);
			cpu.LD_D_H(0);
			cpu.LD_E_H(0);
			cpu.LD_H_H(0);
			cpu.LD_L_H(0);
			Assert::IsTrue(registers.B == value);
			Assert::IsTrue(registers.C == value);
			Assert::IsTrue(registers.D == value);
			Assert::IsTrue(registers.E == value);
			Assert::IsTrue(registers.H == value);
			Assert::IsTrue(registers.L == value);
			registers.Reset();

			registers.L = value;
			cpu.LD_A_L(0);
			cpu.LD_B_L(0);
			cpu.LD_C_L(0);
			cpu.LD_D_L(0);
			cpu.LD_E_L(0);
			cpu.LD_H_L(0);
			cpu.LD_L_L(0);
			Assert::IsTrue(registers.B == value);
			Assert::IsTrue(registers.C == value);
			Assert::IsTrue(registers.D == value);
			Assert::IsTrue(registers.E == value);
			Assert::IsTrue(registers.H == value);
			Assert::IsTrue(registers.L == value);
			registers.Reset();

			registers.HL = wramAddress;
			memory.WriteByte(registers.HL, value);
			cpu.LD_A_aHL(0);
			cpu.LD_B_aHL(0);
			cpu.LD_C_aHL(0);
			cpu.LD_D_aHL(0);
			cpu.LD_E_aHL(0);
			cpu.LD_H_aHL(0);
			Assert::IsTrue(registers.B == value);
			Assert::IsTrue(registers.C == value);
			Assert::IsTrue(registers.D == value);
			Assert::IsTrue(registers.E == value);
			Assert::IsTrue(registers.H == value);
			registers.HL = wramAddress;
			cpu.LD_L_aHL(0);
			Assert::IsTrue(registers.L == value);
			registers.Reset();

			registers.HL = wramAddress;
			registers.B = value;
			registers.C = value;
			registers.D = value;
			registers.E = value;
			cpu.LD_aHL_B(0);
			Assert::IsTrue(memory.ReadByte(wramAddress) == registers.B);
			cpu.LD_aHL_C(0);
			Assert::IsTrue(memory.ReadByte(wramAddress) == registers.C);
			cpu.LD_aHL_D(0);
			Assert::IsTrue(memory.ReadByte(wramAddress) == registers.D);
			cpu.LD_aHL_E(0);
			Assert::IsTrue(memory.ReadByte(wramAddress) == registers.E);
			cpu.LD_aHL_H(0);
			Assert::IsTrue(memory.ReadByte(wramAddress) == registers.H);
			cpu.LD_aHL_L(0);
			Assert::IsTrue(memory.ReadByte(wramAddress) == registers.L);
			registers.Reset();
		}

		TEST_METHOD(TestCPUInstructions_LD_A_n)
		{
			MemoryMap memory;
			CPU cpu(memory);
			Registers& registers = cpu.GetRegisters();

			registers.Reset();
			Assert::IsTrue(registers.A == 0u);
			Assert::IsTrue(registers.B == 0u);
			Assert::IsTrue(registers.C == 0u);
			Assert::IsTrue(registers.D == 0u);
			Assert::IsTrue(registers.E == 0u);
			Assert::IsTrue(registers.H == 0u);
			Assert::IsTrue(registers.L == 0u);

			uint8_t value = 0xAB;
			uint16_t wramAddress = 0xD000;

			registers.A = value;
			cpu.LD_A_A(0);
			Assert::IsTrue(registers.A == value);
			registers.Reset();

			registers.B = value;
			cpu.LD_A_B(0);
			Assert::IsTrue(registers.A == value);
			registers.Reset();

			registers.C = value;
			cpu.LD_A_C(0);
			Assert::IsTrue(registers.A == value);
			registers.Reset();

			registers.D = value;
			cpu.LD_A_D(0);
			Assert::IsTrue(registers.A == value);
			registers.Reset();

			registers.E = value;
			cpu.LD_A_E(0);
			Assert::IsTrue(registers.A == value);
			registers.Reset();

			registers.H = value;
			cpu.LD_A_H(0);
			Assert::IsTrue(registers.A == value);
			registers.Reset();

			registers.L = value;
			cpu.LD_A_L(0);
			Assert::IsTrue(registers.A == value);
			registers.Reset();

			registers.BC = wramAddress;
			memory.WriteByte(wramAddress, value);
			cpu.LD_A_aBC(0);
			Assert::IsTrue(registers.A == memory.ReadByte(wramAddress));
			registers.Reset();

			registers.DE = wramAddress;
			memory.WriteByte(wramAddress, value);
			cpu.LD_A_aDE(0);
			Assert::IsTrue(registers.A == memory.ReadByte(wramAddress));
			registers.Reset();

			registers.HL = wramAddress;
			memory.WriteByte(wramAddress, value);
			cpu.LD_A_aHL(0);
			Assert::IsTrue(registers.A == memory.ReadByte(wramAddress));
			registers.Reset();

			memory.WriteByte(wramAddress, value);
			cpu.LD_A_ann(wramAddress);
			Assert::IsTrue(registers.A == memory.ReadByte(wramAddress));
			registers.Reset();

			cpu.LD_A_n(value);
			Assert::IsTrue(registers.A == value);
			registers.Reset();
		}

		TEST_METHOD(TestCPUInstructions_LD_n_A)
		{
			MemoryMap memory;
			CPU cpu(memory);
			Registers& registers = cpu.GetRegisters();

			registers.Reset();
			Assert::IsTrue(registers.A == 0u);
			Assert::IsTrue(registers.B == 0u);
			Assert::IsTrue(registers.C == 0u);
			Assert::IsTrue(registers.D == 0u);
			Assert::IsTrue(registers.E == 0u);
			Assert::IsTrue(registers.H == 0u);
			Assert::IsTrue(registers.L == 0u);

			uint8_t value = 0xAB;
			uint16_t wramAddress = 0xD000;

			registers.A = value;
			cpu.LD_A_A(0);
			Assert::IsTrue(registers.A == value);
			registers.Reset();

			registers.A = value;
			cpu.LD_B_A(0);
			Assert::IsTrue(registers.B == value);
			registers.Reset();

			registers.A = value;
			cpu.LD_C_A(0);
			Assert::IsTrue(registers.C == value);
			registers.Reset();

			registers.A = value;
			cpu.LD_D_A(0);
			Assert::IsTrue(registers.D == value);
			registers.Reset();

			registers.A = value;
			cpu.LD_E_A(0);
			Assert::IsTrue(registers.E == value);
			registers.Reset();

			registers.A = value;
			cpu.LD_H_A(0);
			Assert::IsTrue(registers.H == value);
			registers.Reset();

			registers.A = value;
			cpu.LD_L_A(0);
			Assert::IsTrue(registers.L == value);
			registers.Reset();

			registers.BC = wramAddress;
			registers.A = value;
			cpu.LD_aBC_A(0);
			Assert::IsTrue(registers.A == memory.ReadByte(wramAddress));
			registers.Reset();

			registers.DE = wramAddress;
			registers.A = value;
			cpu.LD_aDE_A(0);
			Assert::IsTrue(registers.A == memory.ReadByte(wramAddress));
			registers.Reset();

			registers.HL = wramAddress;
			registers.A = value;
			cpu.LD_aHL_A(0);
			Assert::IsTrue(registers.A == memory.ReadByte(wramAddress));
			registers.Reset();

			registers.A = value;
			cpu.LD_ann_A(wramAddress);
			Assert::IsTrue(registers.A == memory.ReadByte(wramAddress));
			registers.Reset();
		}

		TEST_METHOD(TestCPUInstructions_LD_A_aC)
		{
			MemoryMap memory;
			CPU cpu(memory);
			Registers& registers = cpu.GetRegisters();

			registers.Reset();
			Assert::IsTrue(registers.A == 0u);
			Assert::IsTrue(registers.B == 0u);
			Assert::IsTrue(registers.C == 0u);
			Assert::IsTrue(registers.D == 0u);
			Assert::IsTrue(registers.E == 0u);
			Assert::IsTrue(registers.H == 0u);
			Assert::IsTrue(registers.L == 0u);

			uint8_t value = 0xAB;
			uint16_t wramAddress = 0xFF80;
			uint8_t addressLow = wramAddress & 0xFF;

			memory.WriteByte(wramAddress, value);
			registers.C = addressLow;
			cpu.LD_A_aC(0);
			Assert::IsTrue(registers.A == memory.ReadByte(wramAddress));
			registers.Reset();

			registers.A = value;
			registers.C = addressLow;
			cpu.LD_aC_A(0);
			Assert::IsTrue(registers.A == memory.ReadByte(wramAddress));
			registers.Reset();
		}

		TEST_METHOD(TestCPUInstructions_LD_A_HLDI)
		{
			MemoryMap memory;
			CPU cpu(memory);
			Registers& registers = cpu.GetRegisters();

			registers.Reset();
			Assert::IsTrue(registers.A == 0u);
			Assert::IsTrue(registers.B == 0u);
			Assert::IsTrue(registers.C == 0u);
			Assert::IsTrue(registers.D == 0u);
			Assert::IsTrue(registers.E == 0u);
			Assert::IsTrue(registers.H == 0u);
			Assert::IsTrue(registers.L == 0u);

			uint8_t value = 0xAB;
			uint16_t wramAddress = 0xD000;

			registers.HL = wramAddress;
			memory.WriteByte(wramAddress, value);
			cpu.LDD_A_aHL(0);
			Assert::IsTrue(registers.A == memory.ReadByte(wramAddress));
			Assert::IsTrue(registers.HL == wramAddress - 1);
			registers.Reset();

			registers.HL = wramAddress;
			registers.A = value;
			cpu.LDD_aHL_A(0);
			Assert::IsTrue(registers.A == memory.ReadByte(wramAddress));
			Assert::IsTrue(registers.HL == wramAddress - 1);
			registers.Reset();

			registers.HL = wramAddress;
			memory.WriteByte(wramAddress, value);
			cpu.LDI_A_aHL(0);
			Assert::IsTrue(registers.A == memory.ReadByte(wramAddress));
			Assert::IsTrue(registers.HL == wramAddress + 1);
			registers.Reset();

			registers.HL = wramAddress;
			registers.A = value;
			cpu.LDI_aHL_A(0);
			Assert::IsTrue(registers.A == memory.ReadByte(wramAddress));
			Assert::IsTrue(registers.HL == wramAddress + 1);
			registers.Reset();
		}

		TEST_METHOD(TestCPUInstructions_LDH_A_n)
		{
			MemoryMap memory;
			CPU cpu(memory);
			Registers& registers = cpu.GetRegisters();

			registers.Reset();
			Assert::IsTrue(registers.A == 0u);
			Assert::IsTrue(registers.B == 0u);
			Assert::IsTrue(registers.C == 0u);
			Assert::IsTrue(registers.D == 0u);
			Assert::IsTrue(registers.E == 0u);
			Assert::IsTrue(registers.H == 0u);
			Assert::IsTrue(registers.L == 0u);

			uint8_t value = 0xAB;
			uint16_t wramAddress = 0xFF80;
			uint8_t addressLow = wramAddress & 0xFF;

			memory.WriteByte(wramAddress, value);
			cpu.LDH_A_an(addressLow);
			Assert::IsTrue(registers.A == memory.ReadByte(wramAddress));
			registers.Reset();

			registers.A = value;
			cpu.LDH_an_A(addressLow);
			Assert::IsTrue(registers.A == memory.ReadByte(wramAddress));
			registers.Reset();
		}

		TEST_METHOD(TestCPUInstructions_LD_n_nn)
		{
			MemoryMap memory;
			CPU cpu(memory);
			Registers& registers = cpu.GetRegisters();

			registers.Reset();
			Assert::IsTrue(registers.A == 0u);
			Assert::IsTrue(registers.B == 0u);
			Assert::IsTrue(registers.C == 0u);
			Assert::IsTrue(registers.D == 0u);
			Assert::IsTrue(registers.E == 0u);
			Assert::IsTrue(registers.H == 0u);
			Assert::IsTrue(registers.L == 0u);

			uint16_t value = 0xABCD;

			cpu.LD_BC_nn(value);
			Assert::IsTrue(registers.BC == value);
			registers.Reset();

			cpu.LD_DE_nn(value);
			Assert::IsTrue(registers.DE == value);
			registers.Reset();

			cpu.LD_HL_nn(value);
			Assert::IsTrue(registers.HL == value);
			registers.Reset();

			cpu.LD_SP_nn(value);
			Assert::IsTrue(registers.SP == value);
			registers.Reset();
		}

		TEST_METHOD(TestCPUInstructions_LD_SP_HL)
		{
			MemoryMap memory;
			CPU cpu(memory);
			Registers& registers = cpu.GetRegisters();

			registers.Reset();
			Assert::IsTrue(registers.A == 0u);
			Assert::IsTrue(registers.B == 0u);
			Assert::IsTrue(registers.C == 0u);
			Assert::IsTrue(registers.D == 0u);
			Assert::IsTrue(registers.E == 0u);
			Assert::IsTrue(registers.H == 0u);
			Assert::IsTrue(registers.L == 0u);

			uint16_t value = 0xABCD;
			int8_t offset = 12;

			registers.HL = value;
			cpu.LD_SP_HL(0);
			Assert::IsTrue(registers.SP == value);
			registers.Reset();

			registers.SP = value;
			cpu.LD_HL_SP_n(offset);
			Assert::IsTrue(registers.SP + offset == registers.HL);
			Assert::IsFalse(registers.GetZeroFlag());
			Assert::IsFalse(registers.GetSubtractFlag());
			// TODO test half carry and carry
			registers.Reset();
		}

		TEST_METHOD(TestCPUInstructions_LD_nn_SP)
		{
			MemoryMap memory;
			CPU cpu(memory);
			Registers& registers = cpu.GetRegisters();

			registers.Reset();
			Assert::IsTrue(registers.A == 0u);
			Assert::IsTrue(registers.B == 0u);
			Assert::IsTrue(registers.C == 0u);
			Assert::IsTrue(registers.D == 0u);
			Assert::IsTrue(registers.E == 0u);
			Assert::IsTrue(registers.H == 0u);
			Assert::IsTrue(registers.L == 0u);

			uint16_t value = 0xABCD;
			uint16_t wramAddress = 0xD000;

			registers.SP = value;
			cpu.LD_ann_SP(wramAddress);
			Assert::IsTrue(registers.SP == memory.ReadWord(wramAddress));
			registers.Reset();
		}

		TEST_METHOD(TestCPUInstructions_PUSH_POP)
		{
			MemoryMap memory;
			CPU cpu(memory);
			Registers& registers = cpu.GetRegisters();

			registers.Reset();
			Assert::IsTrue(registers.A == 0u);
			Assert::IsTrue(registers.B == 0u);
			Assert::IsTrue(registers.C == 0u);
			Assert::IsTrue(registers.D == 0u);
			Assert::IsTrue(registers.E == 0u);
			Assert::IsTrue(registers.H == 0u);
			Assert::IsTrue(registers.L == 0u);

			uint16_t value = 0xABCD;
			uint16_t stackAddress = 0xFFFE;

			registers.SP = stackAddress;
			registers.AF = value;
			cpu.PUSH_AF(0);
			Assert::IsTrue(memory.ReadWord(registers.SP) == value);
			Assert::IsTrue(registers.SP == stackAddress - 2);
			cpu.POP_BC(0);
			Assert::IsTrue(registers.BC == value);
			Assert::IsTrue(registers.SP == stackAddress);
			registers.Reset();

			registers.SP = stackAddress;
			registers.BC = value;
			cpu.PUSH_BC(0);
			Assert::IsTrue(memory.ReadWord(registers.SP) == value);
			Assert::IsTrue(registers.SP == stackAddress - 2);
			cpu.POP_DE(0);
			Assert::IsTrue(registers.DE == value);
			Assert::IsTrue(registers.SP == stackAddress);
			registers.Reset();

			registers.SP = stackAddress;
			registers.DE = value;
			cpu.PUSH_DE(0);
			Assert::IsTrue(memory.ReadWord(registers.SP) == value);
			Assert::IsTrue(registers.SP == stackAddress - 2);
			cpu.POP_HL(0);
			Assert::IsTrue(registers.HL == value);
			Assert::IsTrue(registers.SP == stackAddress);
			registers.Reset();

			registers.SP = stackAddress;
			registers.HL = value;
			cpu.PUSH_HL(0);
			Assert::IsTrue(memory.ReadWord(registers.SP) == value);
			Assert::IsTrue(registers.SP == stackAddress - 2);
			cpu.POP_AF(0);
			Assert::IsTrue(registers.AF == value);
			Assert::IsTrue(registers.SP == stackAddress);
			registers.Reset();
		}

		TEST_METHOD(TestCPUInstructions_ADD_A_n)
		{
			MemoryMap memory;
			CPU cpu(memory);
			Registers& registers = cpu.GetRegisters();

			registers.Reset();
			Assert::IsTrue(registers.A == 0u);
			Assert::IsTrue(registers.B == 0u);
			Assert::IsTrue(registers.C == 0u);
			Assert::IsTrue(registers.D == 0u);
			Assert::IsTrue(registers.E == 0u);
			Assert::IsTrue(registers.H == 0u);
			Assert::IsTrue(registers.L == 0u);

			uint8_t value = 0xAB;
			uint8_t addMe = 0x12;
			uint16_t wramAddress = 0xD000;

			// TODO test flags for all of this

			registers.A = value;
			cpu.ADD_A_A(0);
			Assert::IsTrue(registers.A == ((value + value) & 0xFF));
			registers.Reset();

			registers.A = value;
			registers.B = addMe;
			cpu.ADD_A_B(0);
			Assert::IsTrue(registers.A == ((value + addMe) & 0xFF));
			registers.Reset();

			registers.A = value;
			registers.C = addMe;
			cpu.ADD_A_C(0);
			Assert::IsTrue(registers.A == ((value + addMe) & 0xFF));
			registers.Reset();

			registers.A = value;
			registers.D = addMe;
			cpu.ADD_A_D(0);
			Assert::IsTrue(registers.A == ((value + addMe) & 0xFF));
			registers.Reset();

			registers.A = value;
			registers.E = addMe;
			cpu.ADD_A_E(0);
			Assert::IsTrue(registers.A == ((value + addMe) & 0xFF));
			registers.Reset();

			registers.A = value;
			registers.H = addMe;
			cpu.ADD_A_H(0);
			Assert::IsTrue(registers.A == ((value + addMe) & 0xFF));
			registers.Reset();

			registers.A = value;
			registers.L = addMe;
			cpu.ADD_A_L(0);
			Assert::IsTrue(registers.A == ((value + addMe) & 0xFF));
			registers.Reset();

			registers.A = value;
			registers.HL = wramAddress;
			memory.WriteByte(wramAddress, addMe);
			cpu.ADD_A_aHL(0);
			Assert::IsTrue(registers.A == ((value + addMe) & 0xFF));
			registers.Reset();

			registers.A = value;
			cpu.ADD_A_n(addMe);
			Assert::IsTrue(registers.A == ((value + addMe) & 0xFF));
			registers.Reset();
		}

		TEST_METHOD(TestCPUInstructions_ADC_A_n)
		{
			MemoryMap memory;
			CPU cpu(memory);
			Registers& registers = cpu.GetRegisters();

			registers.Reset();
			Assert::IsTrue(registers.A == 0u);
			Assert::IsTrue(registers.B == 0u);
			Assert::IsTrue(registers.C == 0u);
			Assert::IsTrue(registers.D == 0u);
			Assert::IsTrue(registers.E == 0u);
			Assert::IsTrue(registers.H == 0u);
			Assert::IsTrue(registers.L == 0u);

			uint8_t value = 0xAB;
			uint8_t addMe = 0x12;
			uint16_t wramAddress = 0xD000;

			// TODO test flags for all of this

			registers.A = value;
			registers.SetCarryFlag();
			cpu.ADC_A_A(0);
			Assert::IsTrue(registers.A == ((value + value + 1) & 0xFF));
			registers.Reset();

			registers.A = value;
			registers.B = addMe;
			registers.SetCarryFlag();
			cpu.ADC_A_B(0);
			Assert::IsTrue(registers.A == ((value + addMe + 1) & 0xFF));
			registers.Reset();

			registers.A = value;
			registers.C = addMe;
			registers.SetCarryFlag();
			cpu.ADC_A_C(0);
			Assert::IsTrue(registers.A == ((value + addMe + 1) & 0xFF));
			registers.Reset();

			registers.A = value;
			registers.D = addMe;
			cpu.ADD_A_D(0);
			Assert::IsTrue(registers.A == ((value + addMe) & 0xFF));
			registers.Reset();

			registers.A = value;
			registers.E = addMe;
			registers.SetCarryFlag();
			cpu.ADC_A_E(0);
			Assert::IsTrue(registers.A == ((value + addMe + 1) & 0xFF));
			registers.Reset();

			registers.A = value;
			registers.H = addMe;
			registers.SetCarryFlag();
			cpu.ADC_A_H(0);
			Assert::IsTrue(registers.A == ((value + addMe + 1) & 0xFF));
			registers.Reset();

			registers.A = value;
			registers.L = addMe;
			registers.SetCarryFlag();
			cpu.ADC_A_L(0);
			Assert::IsTrue(registers.A == ((value + addMe + 1) & 0xFF));
			registers.Reset();

			registers.A = value;
			registers.HL = wramAddress;
			registers.SetCarryFlag();
			memory.WriteByte(wramAddress, addMe);
			cpu.ADC_A_aHL(0);
			Assert::IsTrue(registers.A == ((value + addMe + 1) & 0xFF));
			registers.Reset();

			registers.A = value;
			registers.SetCarryFlag();
			cpu.ADC_A_n(addMe);
			Assert::IsTrue(registers.A == ((value + addMe + 1) & 0xFF));
			registers.Reset();
		}

		TEST_METHOD(TestCPUInstructions_SUB_n)
		{
			MemoryMap memory;
			CPU cpu(memory);
			Registers& registers = cpu.GetRegisters();

			registers.Reset();
			Assert::IsTrue(registers.A == 0u);
			Assert::IsTrue(registers.B == 0u);
			Assert::IsTrue(registers.C == 0u);
			Assert::IsTrue(registers.D == 0u);
			Assert::IsTrue(registers.E == 0u);
			Assert::IsTrue(registers.H == 0u);
			Assert::IsTrue(registers.L == 0u);

			uint8_t value = 0xAB;
			uint8_t subMe = 0x12;
			uint16_t wramAddress = 0xD000;

			// TODO test flags for all of this

			registers.A = value;
			cpu.SUB_A(0);
			Assert::IsTrue(registers.A == ((value - value) & 0xFF));
			registers.Reset();

			registers.A = value;
			registers.B = subMe;
			cpu.SUB_B(0);
			Assert::IsTrue(registers.A == ((value - subMe) & 0xFF));
			registers.Reset();

			registers.A = value;
			registers.C = subMe;
			cpu.SUB_C(0);
			Assert::IsTrue(registers.A == ((value - subMe) & 0xFF));
			registers.Reset();

			registers.A = value;
			registers.D = subMe;
			cpu.SUB_D(0);
			Assert::IsTrue(registers.A == ((value - subMe) & 0xFF));
			registers.Reset();

			registers.A = value;
			registers.E = subMe;
			cpu.SUB_E(0);
			Assert::IsTrue(registers.A == ((value - subMe) & 0xFF));
			registers.Reset();

			registers.A = value;
			registers.H = subMe;
			cpu.SUB_H(0);
			Assert::IsTrue(registers.A == ((value - subMe) & 0xFF));
			registers.Reset();

			registers.A = value;
			registers.L = subMe;
			cpu.SUB_L(0);
			Assert::IsTrue(registers.A == ((value - subMe) & 0xFF));
			registers.Reset();

			registers.A = value;
			registers.HL = wramAddress;
			memory.WriteByte(wramAddress, subMe);
			cpu.SUB_aHL(0);
			Assert::IsTrue(registers.A == ((value - subMe) & 0xFF));
			registers.Reset();

			registers.A = value;
			cpu.SUB_n(subMe);
			Assert::IsTrue(registers.A == ((value - subMe) & 0xFF));
			registers.Reset();
		}

		TEST_METHOD(TestCPUInstructions_SBC_A_n)
		{
			MemoryMap memory;
			CPU cpu(memory);
			Registers& registers = cpu.GetRegisters();

			registers.Reset();
			Assert::IsTrue(registers.A == 0u);
			Assert::IsTrue(registers.B == 0u);
			Assert::IsTrue(registers.C == 0u);
			Assert::IsTrue(registers.D == 0u);
			Assert::IsTrue(registers.E == 0u);
			Assert::IsTrue(registers.H == 0u);
			Assert::IsTrue(registers.L == 0u);

			uint8_t value = 0xAB;
			uint8_t subMe = 0x12;
			uint16_t wramAddress = 0xD000;

			// TODO test flags for all of this

			registers.A = value;
			registers.SetCarryFlag();
			cpu.SBC_A_A(0);
			Assert::IsTrue(registers.A == ((value - (value + 1)) & 0xFF));
			registers.Reset();

			registers.A = value;
			registers.B = subMe;
			registers.SetCarryFlag();
			cpu.SBC_A_B(0);
			Assert::IsTrue(registers.A == ((value - (subMe + 1)) & 0xFF));
			registers.Reset();

			registers.A = value;
			registers.C = subMe;
			registers.SetCarryFlag();
			cpu.SBC_A_C(0);
			Assert::IsTrue(registers.A == ((value - (subMe + 1)) & 0xFF));
			registers.Reset();

			registers.A = value;
			registers.D = subMe;
			registers.SetCarryFlag();
			cpu.SBC_A_D(0);
			Assert::IsTrue(registers.A == ((value - (subMe + 1)) & 0xFF));
			registers.Reset();

			registers.A = value;
			registers.E = subMe;
			registers.SetCarryFlag();
			cpu.SBC_A_E(0);
			Assert::IsTrue(registers.A == ((value - (subMe + 1)) & 0xFF));
			registers.Reset();

			registers.A = value;
			registers.H = subMe;
			registers.SetCarryFlag();
			cpu.SBC_A_H(0);
			Assert::IsTrue(registers.A == ((value - (subMe + 1)) & 0xFF));
			registers.Reset();

			registers.A = value;
			registers.L = subMe;
			registers.SetCarryFlag();
			cpu.SBC_A_L(0);
			Assert::IsTrue(registers.A == ((value - (subMe + 1)) & 0xFF));
			registers.Reset();

			registers.A = value;
			registers.HL = wramAddress;
			registers.SetCarryFlag();
			memory.WriteByte(wramAddress, subMe);
			cpu.SBC_A_aHL(0);
			Assert::IsTrue(registers.A == ((value - (subMe + 1)) & 0xFF));
			registers.Reset();

			registers.A = value;
			registers.SetCarryFlag();
			cpu.SBC_A_n(subMe);
			Assert::IsTrue(registers.A == ((value - (subMe + 1)) & 0xFF));
			registers.Reset();
		}

		TEST_METHOD(TestCPUInstructions_AND_n)
		{
			MemoryMap memory;
			CPU cpu(memory);
			Registers& registers = cpu.GetRegisters();

			registers.Reset();
			Assert::IsTrue(registers.A == 0u);
			Assert::IsTrue(registers.B == 0u);
			Assert::IsTrue(registers.C == 0u);
			Assert::IsTrue(registers.D == 0u);
			Assert::IsTrue(registers.E == 0u);
			Assert::IsTrue(registers.H == 0u);
			Assert::IsTrue(registers.L == 0u);

			uint8_t value = 0x0F;
			uint8_t andMe = 0xF0;
			uint8_t anded = value & andMe;
			uint16_t wramAddress = 0xD000;

			// TODO test flags for all of this

			registers.A = value;
			cpu.AND_A(0);
			Assert::IsTrue(registers.A == value);
			registers.Reset();

			registers.A = value;
			registers.B = andMe;
			cpu.AND_B(0);
			Assert::IsTrue(registers.A == anded);
			registers.Reset();

			registers.A = value;
			registers.C = andMe;
			cpu.AND_C(0);
			Assert::IsTrue(registers.A == anded);
			registers.Reset();

			registers.A = value;
			registers.D = andMe;
			cpu.AND_D(0);
			Assert::IsTrue(registers.A == anded);
			registers.Reset();

			registers.A = value;
			registers.E = andMe;
			cpu.AND_E(0);
			Assert::IsTrue(registers.A == anded);
			registers.Reset();

			registers.A = value;
			registers.H = andMe;
			cpu.AND_H(0);
			Assert::IsTrue(registers.A == anded);
			registers.Reset();

			registers.A = value;
			registers.L = andMe;
			cpu.AND_L(0);
			Assert::IsTrue(registers.A == anded);
			registers.Reset();

			registers.A = value;
			registers.HL = wramAddress;
			memory.WriteByte(wramAddress, andMe);
			cpu.AND_aHL(0);
			Assert::IsTrue(registers.A == anded);
			registers.Reset();

			registers.A = value;
			cpu.AND_n(andMe);
			Assert::IsTrue(registers.A == anded);
			registers.Reset();
		}

		TEST_METHOD(TestCPUInstructions_OR_n)
		{
			MemoryMap memory;
			CPU cpu(memory);
			Registers& registers = cpu.GetRegisters();

			registers.Reset();
			Assert::IsTrue(registers.A == 0u);
			Assert::IsTrue(registers.B == 0u);
			Assert::IsTrue(registers.C == 0u);
			Assert::IsTrue(registers.D == 0u);
			Assert::IsTrue(registers.E == 0u);
			Assert::IsTrue(registers.H == 0u);
			Assert::IsTrue(registers.L == 0u);

			uint8_t value = 0x0F;
			uint8_t orMe = 0xF0;
			uint8_t ored = value | orMe;
			uint16_t wramAddress = 0xD000;

			// TODO test flags for all of this

			registers.A = value;
			cpu.OR_A(0);
			Assert::IsTrue(registers.A == value);
			registers.Reset();

			registers.A = value;
			registers.B = orMe;
			cpu.OR_B(0);
			Assert::IsTrue(registers.A == ored);
			registers.Reset();

			registers.A = value;
			registers.C = orMe;
			cpu.OR_C(0);
			Assert::IsTrue(registers.A == ored);
			registers.Reset();

			registers.A = value;
			registers.D = orMe;
			cpu.OR_D(0);
			Assert::IsTrue(registers.A == ored);
			registers.Reset();

			registers.A = value;
			registers.E = orMe;
			cpu.OR_E(0);
			Assert::IsTrue(registers.A == ored);
			registers.Reset();

			registers.A = value;
			registers.H = orMe;
			cpu.OR_H(0);
			Assert::IsTrue(registers.A == ored);
			registers.Reset();

			registers.A = value;
			registers.L = orMe;
			cpu.OR_L(0);
			Assert::IsTrue(registers.A == ored);
			registers.Reset();

			registers.A = value;
			registers.HL = wramAddress;
			memory.WriteByte(wramAddress, orMe);
			cpu.OR_aHL(0);
			Assert::IsTrue(registers.A == ored);
			registers.Reset();

			registers.A = value;
			cpu.OR_n(orMe);
			Assert::IsTrue(registers.A == ored);
			registers.Reset();
		}

		TEST_METHOD(TestCPUInstructions_XOR_n)
		{
			MemoryMap memory;
			CPU cpu(memory);
			Registers& registers = cpu.GetRegisters();

			registers.Reset();
			Assert::IsTrue(registers.A == 0u);
			Assert::IsTrue(registers.B == 0u);
			Assert::IsTrue(registers.C == 0u);
			Assert::IsTrue(registers.D == 0u);
			Assert::IsTrue(registers.E == 0u);
			Assert::IsTrue(registers.H == 0u);
			Assert::IsTrue(registers.L == 0u);

			uint8_t value = 0x0F;
			uint8_t xorMe = 0xF0;
			uint8_t xored = value ^ xorMe;
			uint16_t wramAddress = 0xD000;

			// TODO test flags for all of this

			registers.A = value;
			cpu.XOR_A(0);
			Assert::IsTrue(registers.A == 0x00);
			registers.Reset();

			registers.A = value;
			registers.B = xorMe;
			cpu.XOR_B(0);
			Assert::IsTrue(registers.A == xored);
			registers.Reset();

			registers.A = value;
			registers.C = xorMe;
			cpu.XOR_C(0);
			Assert::IsTrue(registers.A == xored);
			registers.Reset();

			registers.A = value;
			registers.D = xorMe;
			cpu.XOR_D(0);
			Assert::IsTrue(registers.A == xored);
			registers.Reset();

			registers.A = value;
			registers.E = xorMe;
			cpu.XOR_E(0);
			Assert::IsTrue(registers.A == xored);
			registers.Reset();

			registers.A = value;
			registers.H = xorMe;
			cpu.XOR_H(0);
			Assert::IsTrue(registers.A == xored);
			registers.Reset();

			registers.A = value;
			registers.L = xorMe;
			cpu.XOR_L(0);
			Assert::IsTrue(registers.A == xored);
			registers.Reset();

			registers.A = value;
			registers.HL = wramAddress;
			memory.WriteByte(wramAddress, xorMe);
			cpu.XOR_aHL(0);
			Assert::IsTrue(registers.A == xored);
			registers.Reset();

			registers.A = value;
			cpu.XOR_n(xorMe);
			Assert::IsTrue(registers.A == xored);
			registers.Reset();
		}

		TEST_METHOD(TestCPUInstructions_CP_n)
		{
			MemoryMap memory;
			CPU cpu(memory);
			Registers& registers = cpu.GetRegisters();

			registers.Reset();
			Assert::IsTrue(registers.A == 0u);
			Assert::IsTrue(registers.B == 0u);
			Assert::IsTrue(registers.C == 0u);
			Assert::IsTrue(registers.D == 0u);
			Assert::IsTrue(registers.E == 0u);
			Assert::IsTrue(registers.H == 0u);
			Assert::IsTrue(registers.L == 0u);

			uint8_t value = 0xAB;
			uint8_t notValue = 0xBA;
			uint16_t wramAddress = 0xD000;

			// TODO test remaining flags for all of this

			registers.A = value;
			cpu.CP_A(0);
			Assert::IsTrue(registers.GetZeroFlag());
			registers.Reset();

			registers.A = value;
			registers.B = value;
			cpu.CP_B(0);
			Assert::IsTrue(registers.GetZeroFlag());
			registers.B = notValue;
			cpu.CP_B(0);
			Assert::IsFalse(registers.GetZeroFlag());
			registers.Reset();

			registers.A = value;
			registers.C = value;
			cpu.CP_C(0);
			Assert::IsTrue(registers.GetZeroFlag());
			registers.C = notValue;
			cpu.CP_C(0);
			Assert::IsFalse(registers.GetZeroFlag());
			registers.Reset();

			registers.A = value;
			registers.D = value;
			cpu.CP_D(0);
			Assert::IsTrue(registers.GetZeroFlag());
			registers.D = notValue;
			cpu.CP_D(0);
			Assert::IsFalse(registers.GetZeroFlag());
			registers.Reset();

			registers.A = value;
			registers.E = value;
			cpu.CP_E(0);
			Assert::IsTrue(registers.GetZeroFlag());
			registers.E = notValue;
			cpu.CP_E(0);
			Assert::IsFalse(registers.GetZeroFlag());
			registers.Reset();

			registers.A = value;
			registers.H = value;
			cpu.CP_H(0);
			Assert::IsTrue(registers.GetZeroFlag());
			registers.H = notValue;
			cpu.CP_H(0);
			Assert::IsFalse(registers.GetZeroFlag());
			registers.Reset();

			registers.A = value;
			registers.L = value;
			cpu.CP_L(0);
			Assert::IsTrue(registers.GetZeroFlag());
			registers.L = notValue;
			cpu.CP_L(0);
			Assert::IsFalse(registers.GetZeroFlag());
			registers.Reset();

			registers.A = value;
			registers.HL = wramAddress;
			memory.WriteByte(wramAddress, value);
			cpu.CP_aHL(0);
			Assert::IsTrue(registers.GetZeroFlag());
			memory.WriteByte(wramAddress, notValue);
			cpu.CP_aHL(0);
			Assert::IsFalse(registers.GetZeroFlag());
			registers.Reset();

			registers.A = value;
			cpu.CP_n(value);
			Assert::IsTrue(registers.GetZeroFlag());
			cpu.CP_n(notValue);
			Assert::IsFalse(registers.GetZeroFlag());
			registers.Reset();
		}

		TEST_METHOD(TestCPUInstructions_INC_n)
		{
			MemoryMap memory;
			CPU cpu(memory);
			Registers& registers = cpu.GetRegisters();

			registers.Reset();
			Assert::IsTrue(registers.A == 0u);
			Assert::IsTrue(registers.B == 0u);
			Assert::IsTrue(registers.C == 0u);
			Assert::IsTrue(registers.D == 0u);
			Assert::IsTrue(registers.E == 0u);
			Assert::IsTrue(registers.H == 0u);
			Assert::IsTrue(registers.L == 0u);

			uint8_t value = 0xAB;
			uint16_t wramAddress = 0xD000;

			// TODO test flags for all of this

			registers.A = value;
			cpu.INC_A(0);
			Assert::IsTrue(registers.A == ((value + 1) & 0xFF));
			registers.Reset();

			registers.B = value;
			cpu.INC_B(0);
			Assert::IsTrue(registers.B == ((value + 1) & 0xFF));
			registers.Reset();

			registers.C = value;
			cpu.INC_C(0);
			Assert::IsTrue(registers.C == ((value + 1) & 0xFF));
			registers.Reset();

			registers.D = value;
			cpu.INC_D(0);
			Assert::IsTrue(registers.D == ((value + 1) & 0xFF));
			registers.Reset();

			registers.E = value;
			cpu.INC_E(0);
			Assert::IsTrue(registers.E == ((value + 1) & 0xFF));
			registers.Reset();

			registers.H = value;
			cpu.INC_H(0);
			Assert::IsTrue(registers.H == ((value + 1) & 0xFF));
			registers.Reset();

			registers.L = value;
			cpu.INC_L(0);
			Assert::IsTrue(registers.L == ((value + 1) & 0xFF));
			registers.Reset();

			registers.HL = wramAddress;
			memory.WriteByte(wramAddress, value);
			cpu.INC_aHL(0);
			Assert::IsTrue(memory.ReadByte(wramAddress) == ((value + 1) & 0xFF));
			registers.Reset();
		}

		TEST_METHOD(TestCPUInstructions_DEC_n)
		{
			MemoryMap memory;
			CPU cpu(memory);
			Registers& registers = cpu.GetRegisters();

			registers.Reset();
			Assert::IsTrue(registers.A == 0u);
			Assert::IsTrue(registers.B == 0u);
			Assert::IsTrue(registers.C == 0u);
			Assert::IsTrue(registers.D == 0u);
			Assert::IsTrue(registers.E == 0u);
			Assert::IsTrue(registers.H == 0u);
			Assert::IsTrue(registers.L == 0u);

			uint8_t value = 0xAB;
			uint16_t wramAddress = 0xD000;

			// TODO test flags for all of this

			registers.A = value;
			cpu.DEC_A(0);
			Assert::IsTrue(registers.A == ((value - 1) & 0xFF));
			registers.Reset();

			registers.B = value;
			cpu.DEC_B(0);
			Assert::IsTrue(registers.B == ((value - 1) & 0xFF));
			registers.Reset();

			registers.C = value;
			cpu.DEC_C(0);
			Assert::IsTrue(registers.C == ((value - 1) & 0xFF));
			registers.Reset();

			registers.D = value;
			cpu.DEC_D(0);
			Assert::IsTrue(registers.D == ((value - 1) & 0xFF));
			registers.Reset();

			registers.E = value;
			cpu.DEC_E(0);
			Assert::IsTrue(registers.E == ((value - 1) & 0xFF));
			registers.Reset();

			registers.H = value;
			cpu.DEC_H(0);
			Assert::IsTrue(registers.H == ((value - 1) & 0xFF));
			registers.Reset();

			registers.L = value;
			cpu.DEC_L(0);
			Assert::IsTrue(registers.L == ((value - 1) & 0xFF));
			registers.Reset();

			registers.HL = wramAddress;
			memory.WriteByte(wramAddress, value);
			cpu.DEC_aHL(0);
			Assert::IsTrue(memory.ReadByte(wramAddress) == ((value - 1) & 0xFF));
			registers.Reset();
		}

		TEST_METHOD(TestCPUInstructions_ADD_HL_n)
		{
			MemoryMap memory;
			CPU cpu(memory);
			Registers& registers = cpu.GetRegisters();

			registers.Reset();
			Assert::IsTrue(registers.A == 0u);
			Assert::IsTrue(registers.B == 0u);
			Assert::IsTrue(registers.C == 0u);
			Assert::IsTrue(registers.D == 0u);
			Assert::IsTrue(registers.E == 0u);
			Assert::IsTrue(registers.H == 0u);
			Assert::IsTrue(registers.L == 0u);

			uint16_t value = 0xABCD;
			uint16_t addMe = 0x1234;

			// TODO test flags for all of this

			registers.HL = value;
			registers.BC = addMe;
			cpu.ADD_HL_BC(0);
			Assert::IsTrue(registers.HL == ((value + addMe) & 0xFFFF));
			registers.Reset();

			registers.HL = value;
			registers.DE = addMe;
			cpu.ADD_HL_DE(0);
			Assert::IsTrue(registers.HL == ((value + addMe) & 0xFFFF));
			registers.Reset();

			registers.HL = value;
			cpu.ADD_HL_HL(0);
			Assert::IsTrue(registers.HL == ((value + value) & 0xFFFF));
			registers.Reset();

			registers.HL = value;
			registers.SP = addMe;
			cpu.ADD_HL_SP(0);
			Assert::IsTrue(registers.HL == ((value + addMe) & 0xFFFF));
			registers.Reset();
		}

		TEST_METHOD(TestCPUInstructions_ADD_SP_n)
		{
			MemoryMap memory;
			CPU cpu(memory);
			Registers& registers = cpu.GetRegisters();

			registers.Reset();
			Assert::IsTrue(registers.A == 0u);
			Assert::IsTrue(registers.B == 0u);
			Assert::IsTrue(registers.C == 0u);
			Assert::IsTrue(registers.D == 0u);
			Assert::IsTrue(registers.E == 0u);
			Assert::IsTrue(registers.H == 0u);
			Assert::IsTrue(registers.L == 0u);

			uint16_t value = 0xABCD;
			int8_t addMe = 12;

			// TODO test flags for all of this

			registers.SP = value;
			cpu.ADD_SP_n(addMe);
			Assert::IsTrue(registers.SP == ((value + addMe) & 0xFFFF));
			registers.Reset();
		}

		TEST_METHOD(TestCPUInstructions_INC_nn)
		{
			MemoryMap memory;
			CPU cpu(memory);
			Registers& registers = cpu.GetRegisters();

			registers.Reset();
			Assert::IsTrue(registers.A == 0u);
			Assert::IsTrue(registers.B == 0u);
			Assert::IsTrue(registers.C == 0u);
			Assert::IsTrue(registers.D == 0u);
			Assert::IsTrue(registers.E == 0u);
			Assert::IsTrue(registers.H == 0u);
			Assert::IsTrue(registers.L == 0u);

			uint16_t value = 0xABCD;

			// TODO test flags for all of this

			registers.BC = value;
			cpu.INC_BC(0);
			Assert::IsTrue(registers.BC == ((value + 1) & 0xFFFF));
			registers.Reset();

			registers.DE = value;
			cpu.INC_DE(0);
			Assert::IsTrue(registers.DE == ((value + 1) & 0xFFFF));
			registers.Reset();

			registers.HL = value;
			cpu.INC_HL(0);
			Assert::IsTrue(registers.HL == ((value + 1) & 0xFFFF));
			registers.Reset();

			registers.SP = value;
			cpu.INC_SP(0);
			Assert::IsTrue(registers.SP == ((value + 1) & 0xFFFF));
			registers.Reset();
		}

		TEST_METHOD(TestCPUInstructions_DEC_nn)
		{
			MemoryMap memory;
			CPU cpu(memory);
			Registers& registers = cpu.GetRegisters();

			registers.Reset();
			Assert::IsTrue(registers.A == 0u);
			Assert::IsTrue(registers.B == 0u);
			Assert::IsTrue(registers.C == 0u);
			Assert::IsTrue(registers.D == 0u);
			Assert::IsTrue(registers.E == 0u);
			Assert::IsTrue(registers.H == 0u);
			Assert::IsTrue(registers.L == 0u);

			uint16_t value = 0xABCD;

			// TODO test flags for all of this

			registers.BC = value;
			cpu.DEC_BC(0);
			Assert::IsTrue(registers.BC == ((value - 1) & 0xFFFF));
			registers.Reset();

			registers.DE = value;
			cpu.DEC_DE(0);
			Assert::IsTrue(registers.DE == ((value - 1) & 0xFFFF));
			registers.Reset();

			registers.HL = value;
			cpu.DEC_HL(0);
			Assert::IsTrue(registers.HL == ((value - 1) & 0xFFFF));
			registers.Reset();

			registers.SP = value;
			cpu.DEC_SP(0);
			Assert::IsTrue(registers.SP == ((value - 1) & 0xFFFF));
			registers.Reset();
		}

		TEST_METHOD(TestCPUInstructions_SWAP)
		{
			MemoryMap memory;
			CPU cpu(memory);
			Registers& registers = cpu.GetRegisters();

			registers.Reset();
			Assert::IsTrue(registers.A == 0u);
			Assert::IsTrue(registers.B == 0u);
			Assert::IsTrue(registers.C == 0u);
			Assert::IsTrue(registers.D == 0u);
			Assert::IsTrue(registers.E == 0u);
			Assert::IsTrue(registers.H == 0u);
			Assert::IsTrue(registers.L == 0u);

			uint8_t value = 0xAB;
			uint8_t swapped = ((value & 0x0F) << 4) | ((value & 0xF0) >> 4);
			uint16_t wramAddress = 0xD000;

			// TODO test flags for all of this

			registers.A = value;
			cpu.SWAP_A(0);
			Assert::IsTrue(registers.A == swapped);
			registers.Reset();

			registers.B = value;
			cpu.SWAP_B(0);
			Assert::IsTrue(registers.B == swapped);
			registers.Reset();

			registers.C = value;
			cpu.SWAP_C(0);
			Assert::IsTrue(registers.C == swapped);
			registers.Reset();

			registers.D = value;
			cpu.SWAP_D(0);
			Assert::IsTrue(registers.D == swapped);
			registers.Reset();

			registers.E = value;
			cpu.SWAP_E(0);
			Assert::IsTrue(registers.E == swapped);
			registers.Reset();

			registers.H = value;
			cpu.SWAP_H(0);
			Assert::IsTrue(registers.H == swapped);
			registers.Reset();

			registers.L = value;
			cpu.SWAP_L(0);
			Assert::IsTrue(registers.L == swapped);
			registers.Reset();

			registers.HL = wramAddress;
			memory.WriteByte(wramAddress, value);
			cpu.SWAP_aHL(0);
			Assert::IsTrue(memory.ReadByte(wramAddress) == swapped);
		}

		TEST_METHOD(TestCPUInstructions_DAA)
		{
			MemoryMap memory;
			CPU cpu(memory);
			Registers& registers = cpu.GetRegisters();

			registers.Reset();
			Assert::IsTrue(registers.A == 0u);
			Assert::IsTrue(registers.B == 0u);
			Assert::IsTrue(registers.C == 0u);
			Assert::IsTrue(registers.D == 0u);
			Assert::IsTrue(registers.E == 0u);
			Assert::IsTrue(registers.H == 0u);
			Assert::IsTrue(registers.L == 0u);


			// TODO I still don't know what's going on here
			uint8_t value = 0x0F;
			uint8_t daaVal = 0x15;

			// TODO test flags for all of this

			registers.A = value;
			cpu.DAA(0);
			Assert::IsTrue(registers.A == daaVal);
			registers.Reset();
		}

		TEST_METHOD(TestCPUInstructions_CPL)
		{
			MemoryMap memory;
			CPU cpu(memory);
			Registers& registers = cpu.GetRegisters();

			registers.Reset();
			Assert::IsTrue(registers.A == 0u);
			Assert::IsTrue(registers.B == 0u);
			Assert::IsTrue(registers.C == 0u);
			Assert::IsTrue(registers.D == 0u);
			Assert::IsTrue(registers.E == 0u);
			Assert::IsTrue(registers.H == 0u);
			Assert::IsTrue(registers.L == 0u);

			uint8_t value = 0xAB;
			uint8_t complement = ~value;

			registers.A = value;
			cpu.CPL(0);
			Assert::IsTrue(registers.A == complement);
			Assert::IsTrue(registers.GetSubtractFlag());
			Assert::IsTrue(registers.GetHalfCarryFlag());
			registers.Reset();
		}

		TEST_METHOD(TestCPUInstructions_CF)
		{
			MemoryMap memory;
			CPU cpu(memory);
			Registers& registers = cpu.GetRegisters();

			registers.Reset();
			Assert::IsTrue(registers.A == 0u);
			Assert::IsTrue(registers.B == 0u);
			Assert::IsTrue(registers.C == 0u);
			Assert::IsTrue(registers.D == 0u);
			Assert::IsTrue(registers.E == 0u);
			Assert::IsTrue(registers.H == 0u);
			Assert::IsTrue(registers.L == 0u);

			registers.ResetCarryFlag();
			cpu.CCF(0);
			Assert::IsTrue(registers.GetCarryFlag());
			cpu.CCF(0);
			Assert::IsFalse(registers.GetCarryFlag());
			registers.Reset();

			cpu.SCF(0);
			Assert::IsTrue(registers.GetCarryFlag());
			registers.Reset();
		}
	};
}