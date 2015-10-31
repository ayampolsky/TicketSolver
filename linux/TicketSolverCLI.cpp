#include <string.h>
#include <string>

#include "../TicketSolver/TicketSolver.h"

int main (int argc, char **argv)
{
	if (argc != 2) {
		printf ("TicketSolverGUI [-v] [digits]\r\n");
		printf ("  -v     - show version\r\n");
		printf ("  digits - digits of ticket number\r\n");
		printf ("Example\r\n");
		printf ("  TicketSolverGUI 123456\r\n");
		return 0;
	}

	if (!strcmp (argv [1], "-v")) {
		std::string description = "";
		std::string version = "";
		std::string author = "";
		TicketSolver::getVersion(version, description, author);
		printf("%s\r\n", description.c_str());
		printf("Version %s\r\n", version.c_str ());
		printf("Author %s\r\n", author.c_str ());
		return 0;
	}

	if (std::string (argv [1]).find_first_not_of ("0123456789") != std::string::npos) {
		printf("Wrong argument %s, please enter only digits.\r\n", argv[1]);
		return -1;
	}
	
	TicketSolver *ticketSolver = new TicketSolver ();

	//ticketSolver->SolveSingle (argv [1]);
	ticketSolver->Solve(argv [1]);
	const std::list <std::string> &log = ticketSolver->getLog();
	for (std::list <std::string>::const_iterator it = log.begin(); it != log.end(); it++) {
		printf ("%s\r\n", it->c_str());
	}

	delete ticketSolver;
	ticketSolver = NULL;
	
	return 0;
}