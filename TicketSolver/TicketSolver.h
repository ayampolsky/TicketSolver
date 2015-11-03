// Class TicketSolver

#include <string>
#include <list>

class TicketSolver {

private :
  const static std::string version;
  const static std::string description;
  const static std::string author;

  enum Operation {
    OPER_ADD = 0,
    OPER_SUB = 1,
    OPER_DIV = 2,
    OPER_MUL = 3,
    OPER_POW = 4,
    OPER_CAT = 5,
    OPER_MAX = 6,
    OPER_IDL = 7
  };
  const static int OperationPriorities [OPER_MAX];
  const static char *OperationNames [OPER_MAX];

  struct TicketOperation {
    enum Operation operation;
    int closeBracket;
    int openBracket;
  };

  std::string solution;
  std::list <std::string> log;

  std::list<int> numbers;
  std::list<TicketOperation> operations;

  bool useBrackets;

private :
  static std::list<int> ConvertDigits (const std::string digits);
  const std::string writeExpression ();
  int doOperation (std::list<int>::iterator max_it, std::list<TicketOperation>::iterator max_op_it);
  int iterateBrackets (const int targetResult, int &bracketsIterations, int &bracketsSolutions, const bool silent, const bool debug = false);
  int reduceList (std::list<int>::iterator number_begin, std::list<int>::iterator number_end, std::list<TicketOperation>::iterator op_begin, std::list<TicketOperation>::iterator op_end, const bool silent, const int level = 0);

public :
  TicketSolver ();
  ~TicketSolver ();

  int SolveSingle (const std::string digits, const int targetResult);
  int Solve (const std::string digits, const int targetResult);
  const std::list <std::string> getLog () {return log;};

  static void getVersion (std::string &version, std::string &description, std::string &author);
};
