#include "stdafx.h"
#include "StackMachineCommandPrompt.h"

using namespace std;

StackMachineCommandPrompt::StackMachineCommandPrompt(istream & in, ostream & out)
    : m_in(in)
    , m_out(out)
{
}

void StackMachineCommandPrompt::Run()
{
    while (1)
    {
        try
        {
            PrintCommandLineInvitation();
            auto command = ReadCommand();
            ExecuteCommand(command);
        }
        catch (runtime_error const& e)
        {
            m_out << e.what() << endl;
            return;
        }
        catch (exception const& e)
        {
            m_out << e.what() << endl;
        }
    }
}

void StackMachineCommandPrompt::PrintCommandLineInvitation()
{
    m_out << "> ";
}

StackMachineCommandPrompt::Command StackMachineCommandPrompt::ReadCommand()
{
    auto strm     = GetCommandLineStream();
    auto type     = ParseCommandType(strm);
    auto argument = ParseCommandArgument(strm, type);

    return { type, argument };
}

void StackMachineCommandPrompt::ExecuteCommand(Command const& command)
{
    switch (command.type)
    {
    case CommandType::Push:
        return m_stackMachine.Push(command.argument);
    case CommandType::Pop:
        return m_stackMachine.Pop();
    case CommandType::Add:
        return m_stackMachine.Add();
    case CommandType::Multiply:
        return m_stackMachine.Multiply();
    case CommandType::Substract:
        return m_stackMachine.Substract();
    case CommandType::Divide:
        return m_stackMachine.Divide();
    case CommandType::Dump:
        return m_stackMachine.Dump();
    case CommandType::Exit:
        throw runtime_error("Bye Bye");
    case CommandType::Null:
        throw logic_error("Invalid command specified!");
    }
}

int StackMachineCommandPrompt::ParseCommandArgument(istream & in, CommandType const& type) const
{
    int argument = 0;
    if (IsCommandNeedArgument(type))
    {
        if (!(in >> argument))
        {
            throw logic_error("Argument is invalid!");
        }
    }

    return argument;
}

StackMachineCommandPrompt::CommandType StackMachineCommandPrompt::ParseCommandType(istream & in) const
{
    string commandName;
    in >> commandName;
    return GetCommandTypeByName(commandName);
}

istringstream StackMachineCommandPrompt::GetCommandLineStream()
{
    string commandLine;
    getline(m_in, commandLine);
    return istringstream(commandLine);
}

bool StackMachineCommandPrompt::IsCommandNeedArgument(CommandType const& type) const
{
    return type == CommandType::Push;
}

StackMachineCommandPrompt::CommandType StackMachineCommandPrompt::GetCommandTypeByName(string const& name) const
{
    if (name == "push")      return CommandType::Push;
    if (name == "pop")       return CommandType::Pop;
    if (name == "add")       return CommandType::Add;
    if (name == "multiply")  return CommandType::Multiply;
    if (name == "substract") return CommandType::Substract;
    if (name == "divide")    return CommandType::Divide;
    if (name == "dump")      return CommandType::Dump;
    if (name == "exit")      return CommandType::Exit;

    throw logic_error("Invalid command specified!");
}