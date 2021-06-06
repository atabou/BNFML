# BNFML

## ABOUT:

BNFML is a programming language based on the Backus Naur Form (BNF) used to lex and parse the BNF language itself.

## Language Specification:

### Grammar:

The following, is the BNF specification of BNFML:

```EBNF
<BNF> ::= <ListOfBindings>

<ListOfBindings> ::= <ListOfBindings> '\n' <Binding> | <Binding>

<Binding> ::= <NonTerminal> '::=' <OrExpression>

<OrExpression> ::= <OrExpression> '|' <AndExpression> | <AndExpression>

<AndExpression> ::= <AndExpression> <Symbol> | <Symbol>

<Symbol> ::= <NonTerminal> | <Terminal>

<NonTerminal> ::= '<.+>'

<Terminal> ::= '.+'
```

Please note that BNFML is self-descriptive, as such the only specification needed to describe BNFML is BNFML itself. What this means is that the specification you see above is BNFML, and it describes itself.
