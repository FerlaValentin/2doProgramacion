# UNO rules

This document defines the rules the UNO implementation must follow. It is based on the official rules of the classic UNO deck. Where the official rules are vague, this document picks one reading and says so in a note.

Each rule has an identifier (R1, R2, ...) so other parts of the spec and the code can refer to it.

## 1. Terms

- **Hand**: the cards a player holds. Every player can see how many cards each other player has, but not which cards.
- **Draw pile**: face-down stack. Players take cards from its top.
- **Discard pile**: face-up stack. Played cards go on its top. Only the top card matters for the rules.
- **Current color**: the color a played card must match. Usually it is the color of the top discard. After a Wild card it is the color the player chose.
- **Current value**: the number (0-9) or action (Skip, Reverse, Draw Two) of the top discard. After a Wild card there is no current value.
- **Direction**: the order of turns, either clockwise or counterclockwise. "Next player" always means the next player in the current direction.

## 2. The deck

R1. The deck has 108 cards:

| Card | Per color | Colors | Total |
|---|---|---|---|
| 0 | 1 | 4 | 4 |
| 1 to 9 | 2 of each number | 4 | 72 |
| Skip | 2 | 4 | 8 |
| Reverse | 2 | 4 | 8 |
| Draw Two | 2 | 4 | 8 |
| Wild | | no color | 4 |
| Wild Draw Four | | no color | 4 |

The four colors are red, yellow, green and blue. Number cards, Skip, Reverse and Draw Two are **colored cards**. Wild and Wild Draw Four are **wild cards** and have no color of their own.

## 3. Setup

R2. A game has 2 to 10 players, seated in a fixed order.

R3. One player is the dealer. The dealer shuffles the deck and deals 7 cards to each player, one at a time.

R4. The rest of the deck is placed face down as the draw pile. The top card of the draw pile is turned over to start the discard pile.

R5. The starting direction is clockwise. The first player is the player to the dealer's left (the next player clockwise from the dealer).

R6. The first discard card can change how the round starts:

| First discard | What happens |
|---|---|
| Number card | Nothing special. The first player plays normally. |
| Skip | The first player is skipped. The player after them starts. |
| Reverse | The direction becomes counterclockwise and the dealer plays first. |
| Draw Two | The first player draws 2 cards and is skipped. The player after them starts. |
| Wild | The first player chooses the current color, then plays their turn normally. |
| Wild Draw Four | It goes back into the draw pile, the draw pile is shuffled, and a new card is turned over. Repeat until the card is not a Wild Draw Four. |

## 4. A turn

R7. On their turn, a player must do exactly one of these:

- **Play** one card from their hand that is legal (R8), or
- **Draw** one card from the draw pile (R9).

A player may choose to draw even if they hold a legal card.

R8. A card is **legal** to play when at least one of these is true:

- It has the current color.
- It has the current value (same number, or same action symbol). For example, a blue 7 can be played on a red 7, and a green Skip on a yellow Skip.
- It is a wild card. Wild can always be played. Wild Draw Four can always be played too, but see R16 about bluffing.

Only one card is played per turn, even if the player holds several identical cards.

R9. When a player draws, they take the top card of the draw pile into their hand. Then:

- If that card is legal, they may play it immediately. Their turn ends after it.
- If it is not legal, or they decide not to play it, their turn ends.

The player may not play any other card from their hand on this turn.

R10. When a turn ends, play passes to the next player, unless the played card says otherwise (section 5).

## 5. Card effects

The effect of a card applies the moment it is played, including when it is played right after being drawn (R9).

R11. **Number card**: no effect.

R12. **Skip**: the next player loses their turn. Play passes to the player after them.

R13. **Reverse**: the direction flips. Play passes to the next player in the new direction. With exactly 2 players, Reverse works like Skip: the player who played it plays again.

R14. **Draw Two**: the next player draws 2 cards and loses their turn.

R15. **Wild**: the player chooses any of the four colors as the new current color (they may pick the color that was already current). Play passes normally.

R16. **Wild Draw Four**: the player chooses the new current color. The next player draws 4 cards and loses their turn.

The player should only play Wild Draw Four if they hold **no card of the current color**. Cards of a different color that match the current value, and wild cards, do not count. The game does not stop a player from breaking this rule: they may bluff. The bluff is caught with a challenge (R17).

R17. **Challenge**: when a Wild Draw Four is played, the next player may challenge it instead of simply drawing 4. The player who played the Wild Draw Four shows their hand to the challenger only. The check uses the current color as it was **before** the Wild Draw Four was played.

| Result | Who draws | Turn |
|---|---|---|
| Guilty (they had a card of that color) | The player who played the Wild Draw Four draws 4. The challenger draws nothing. | The challenger plays their turn normally. |
| Not guilty | The challenger draws 6 (the 4 plus 2 as penalty). | The challenger loses their turn. |

In both cases the Wild Draw Four stays on the discard pile and the color chosen with it stays as the current color.

> Note: the official rules do not say clearly whether a challenger who wins still loses their turn. This spec says they do not: the penalty moves entirely to the bluffer.

R18. Draw penalties never stack. A player who must draw 2 or 4 cannot answer with their own Draw Two or Wild Draw Four to pass the penalty along. They draw, and their turn is lost.

## 6. Running out of draw pile

R19. If a player has to draw and the draw pile is empty, take every card of the discard pile except the top card, shuffle them, and place them face down as the new draw pile. Then continue drawing. This can happen in the middle of a multi-card draw (Draw Two, Wild Draw Four, penalties).

Wild cards that go back into the draw pile lose the color that was chosen for them. They are plain wild cards again.

R20. If the draw pile is still empty after R19 (every other card is in players' hands), the player simply draws nothing. If they were drawing on their own turn (R9), their turn ends.

## 7. Saying "UNO"

R21. When a player plays a card and is left with exactly one card, they must say "UNO". In the implementation this is an explicit action (for example a button) that the player can take before or while playing that card.

R22. If they did not say "UNO", any other player may catch them. Catching is allowed from the moment the card is played until the next player starts their turn (plays or draws). A player who is caught draws 2 cards. After that window closes, they can no longer be caught for that card.

R23. A player who says "UNO" when it does not apply gets no penalty.

## 8. End of a round

R24. A round ends as soon as a player plays their last card. That player wins the round.

R25. If the last card is a Draw Two or a Wild Draw Four, the next player still draws the cards before the round is scored. A Wild Draw Four played as a last card can still be challenged (R17); if the challenge succeeds, the player who played it draws 4, so they are no longer out of cards and the round continues.

## 9. Scoring and winning the game

R26. The round winner scores points for every card still in the other players' hands:

| Card | Points |
|---|---|
| Number card | Its number (0 to 9) |
| Skip, Reverse, Draw Two | 20 |
| Wild, Wild Draw Four | 50 |

R27. The first player to reach **500 points** or more wins the game. If nobody has 500 yet, a new round starts: all cards are collected and shuffled, the dealer role passes to the next player clockwise, and setup (section 3) is repeated.

> Note: an implementation may offer single-round games instead. In that case the round winner (R24) is the game winner and scoring is optional.

## 10. Summary of a turn

For quick reference, the order of events in one turn:

1. If the previous card forces this player to draw (Draw Two, Wild Draw Four), resolve it: for Wild Draw Four the player first decides whether to challenge (R17). The player draws as required and, unless a challenge succeeded, the turn ends here.
2. Otherwise the player either plays a legal card (R8) or draws one card (R9).
3. If the card played is wild, the player chooses the new current color.
4. If the player is left with one card, the "UNO" rules apply (R21-R22).
5. If the player is left with no cards, the round ends (R24-R25).
6. The card's effect decides who plays next (R11-R16).
