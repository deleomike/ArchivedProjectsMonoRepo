package validation;

public class CheckValidInput {
    protected String OnlyLetters;
    protected String OnlyNumber;
    protected String DateFormat;
    protected String EmailFormat;

    public CheckValidInput(){
        OnlyLetters = "[A-Za-z]*";
        OnlyNumber = "\\d*";
        DateFormat = "\\d{2}/\\d{2}/\\d{4}";
        EmailFormat = "\\S*@\\S*.\\w{3}";
    }

    public boolean Check_OnlyLetters(String Check){ return Check.matches(OnlyLetters); }
    public boolean Check_OnlyNumber(String Check){ return Check.matches(OnlyNumber); }
    public boolean Check_DateFormat(String Check){ return Check.matches(DateFormat); }
    public boolean Check_EmailFormat(String Check){ return Check.matches(EmailFormat); }
}
