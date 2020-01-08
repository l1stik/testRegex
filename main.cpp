//
//  main.cpp
//  test2
//
//  Created by Илья on 03.01.2020.
//  Copyright © 2020 Илья. All rights reserved.
//

#include <iostream>
#include "Regex.h"

using namespace std;

int main()
{
    cout << Regex::IsMatch("*ccb.", "aa ccb aa c") << endl;
    
    return 0;
}
