defmodule Solution do
  @spec match_players_and_trainers(players :: [integer], trainers :: [integer]) :: integer
  def match_players_and_trainers(players, trainers) do
    # Sort both arrays to use greedy two-pointer approach
    sorted_players = Enum.sort(players)
    sorted_trainers = Enum.sort(trainers)
    
    do_match(sorted_players, sorted_trainers, 0)
  end

  # Base cases: if either list is empty, we can't make more matches
  defp do_match([], _, count), do: count
  defp do_match(_, [], count), do: count
  
  defp do_match([p | rest_p] = players, [t | rest_t], count) do
    if p <= t do
      # Match found: current trainer satisfies current player
      # Move to next player and next trainer
      do_match(rest_p, rest_t, count + 1)
    else
      # No match: current trainer is too weak for current player
      # Move to next trainer (try to find a stronger one for this player)
      # Keep the current player
      do_match(players, rest_t, count)
    end
  end
end
