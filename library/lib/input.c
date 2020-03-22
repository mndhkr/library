//
//  input.c
//  library
//
//  Created by Shimoda on 22/03/2020.
//  Copyright © 2020 Shimoda. All rights reserved.
//

#include "stdinclude.h"

string input(char* output) {
    string buffer = alloc(4096, sizeof(char));
    printf("%s", output);
    fgets(buffer, 4095, stdin);
    string read = strCopy(buffer);
    release(&buffer);
    return read;
}
