typedef struct {} CODEBUCH;

CODEBUCH codebuch_new_from_frequency(unsigned int f[256]);
CODEBUCH codebuch_new_from_structur(BITARRAY structure);

BITARRAY codebuch_code_for_char(CODEBUCH cb, char c);
char codebuch_char_for_code(CODEBUCH cb, BITARRAY c);

BITARRAY codebuch_structure(CODEBUCH cb);
