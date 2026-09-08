// Three legal main signatures
int main() { return 0; }

int main(int argc, char* argv[]) {
    (void)argc; (void)argv;
    return 0;
}

// C++20 also allows:
int main(int argc, char* argv[]) requires true;  // (no — this is a joke; the two above are the real ones)


