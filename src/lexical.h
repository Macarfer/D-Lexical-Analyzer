/*
*
* This file is gonna store the neccesary resources
* for performing a lexical analysis.
* I'ts structure is gonna be somewhat similar to the on lex uses.
*/

EndOfFile:
    \u0000
    \u001A

EndOfLine:
    \u000D
    \u000A
    \u000D \u000A
    \u2028
    \u2029
    EndOfFile

WhiteSpace:
    Space
    Space WhiteSpace

Space:
    \u0020
    \u0009
    \u000B
    \u000C

Comment:
    BlockComment
    LineComment
    NestingBlockComment

BlockComment:
    /* Characters */

LineComment:
    // Characters EndOfLine

NestingBlockComment:
    /+ NestingBlockCommentCharacters +/

NestingBlockCommentCharacters:
    NestingBlockCommentCharacter
    NestingBlockCommentCharacter NestingBlockCommentCharacters

NestingBlockCommentCharacter:
    Character
    NestingBlockComment

Characters:
    Character
    Character Characters

Token:
    Identifier
    StringLiteral
    CharacterLiteral
    IntegerLiteral
    FloatLiteral
    Keyword
    /
    /=
    .
    ..
    ...
    &
    &=
    &&
    |
    |=
    ||
    -
    -=
    --
    +
    +=
    ++
    <
    <=
    <<
    <<=
    <>
    <>=
    >
    >=
    >>=
    >>>=
    >>
    >>>
    !
    !=
    !<>
    !<>=
    !<
    !<=
    !>
    !>=
    (
    )
    [
    ]
    {
    }
    ?
    ,
    ;
    :
    $
    =
    ==
    *
    *=
    %
    %=
    ^
    ^=
    ^^
    ^^=
    ~
    ~=
    @
    =>
    #

Keyword:
    abstract
    alias
    align
    asm
    assert
    auto

    body
    bool
    break
    byte

    case
    cast
    catch
    cdouble
    cent
    cfloat
    char
    class
    const
    continue
    creal

    dchar
    debug
    default
    delegate
    delete (deprecated)
    deprecated
    do
    double

    else
    enum
    export
    extern

    false
    final
    finally
    float
    for
    foreach
    foreach_reverse
    function

    goto

    idouble
    if
    ifloat
    immutable
    import
    in
    inout
    int
    interface
    invariant
    ireal
    is

    lazy
    long

    macro (unused)
    mixin
    module

    new
    nothrow
    null

    out
    override

    package
    pragma
    private
    protected
    public
    pure

    real
    ref
    return

    scope
    shared
    short
    static
    struct
    super
    switch
    synchronized

    template
    this
    throw
    true
    try
    typedef (deprecated)
    typeid
    typeof

    ubyte
    ucent
    uint
    ulong
    union
    unittest
    ushort

    version
    void
    volatile (deprecated)

    wchar
    while
    with

    __FILE__
    __FILE_FULL_PATH__
    __MODULE__
    __LINE__
    __FUNCTION__
    __PRETTY_FUNCTION__

    __gshared
    __traits
    __vector
    __parameters