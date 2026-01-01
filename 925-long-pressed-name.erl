-spec is_long_pressed_name(Name :: unicode:unicode_binary(), Typed :: unicode:unicode_binary()) -> boolean().
is_long_pressed_name(Name, Typed) ->
    check(Name, Typed, -1).

check(<<>>, <<>>, _) -> true;
check(<<>>, <<T, Rest/binary>>, Last) when T =:= Last ->
    check(<<>>, Rest, Last);
check(<<N, NRest/binary>>, <<T, TRest/binary>>, _) when N =:= T ->
    check(NRest, TRest, N);
check(Name, <<T, TRest/binary>>, Last) when T =:= Last ->
    check(Name, TRest, Last);
check(_, _, _) -> false.
