// these are the platform specific controls for controlling the shell
class Controls {
  public:
    // setup whatever is needed to start controlling a user's shell
    void setup();

    // print using the platform specific print method
    int print(const char *);
    // print using the platform specific print method
    int print(const char *, const int);
    // print using the platform specific print method
    int print(const char *, const char *);

    // get the user input
    char get_user_input();

    // release the user's shell
    void teardown();
};
