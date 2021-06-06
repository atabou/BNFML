# BNFML

## ABOUT:

BNFML is a programming language based on the Backus Naur Form (BNF) used to lex and parse the BNF language itself.

## Language Specification:

### Grammar:

The following, is the BNF specification of BNFML:

```EBNF
<BNF> ::= <ListOfBindings> | <empty>

<ListOfBindings> ::= <ListOfBindings> <Binding> | <Binding>

<Binding> ::= <NonTerminal> '::=' <OrExpression>

<OrExpression> ::= <OrExpression> '|' <AndExpression> | <AndExpression>

<AndExpression> ::= <AndExpression> <Expression> | <Expression>

<Expression> ::= <NonTerminal> | <Terminal>

<NonTerminal> ::= '<.+>'

<Terminal> ::= '.+'

<empty> ::= ''
```

Please note that BNFML is self-descriptive, as such the only specification needed to describe BNFML is BNFML itself. What this means is that the specification you see above is BNFML, and it describes itself.
