package com.company;

import validation.CheckValidInput;

public class ModifiedCheck extends CheckValidInput {

    public ModifiedCheck(){
        super();
        OnlyLetters = "(\\d||\\w||\\s)*";
        OnlyNumber = DateFormat = EmailFormat = OnlyLetters;
    }
}
