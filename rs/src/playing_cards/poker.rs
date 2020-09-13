/// NOTE: Aces are counted as High, so A2345 is not a straight
use super::{Card, ParseCardError, Rank};
use std::{cmp::Ordering, collections::HashMap, str::FromStr};

/// A poker hand
///
/// `cards` is not public because the order matters.
/// `cards` must be ordered highest to lowest in rank, suit does not matter.
#[derive(PartialEq, Eq, Debug)]
pub struct Hand {
    cards: [Card; 5],
}

impl Hand {
    pub fn new(mut cards: [Card; 5]) -> Self {
        cards.sort_by(|a, b| a.rank.cmp(&b.rank).reverse());
        Self { cards }
    }

    fn score(&self) -> Score {
        let counts = self.counts();
        let mut flipped_counts = HashMap::new();
        for (rank, count) in counts {
            flipped_counts
                .entry(count)
                .or_insert_with(Vec::new)
                .push(rank);
        }
        // I think this is necessary because the order of the iteration through counts above is not known, since its a HashMap
        for (_count, ranks) in flipped_counts.iter_mut() {
            ranks.sort_by(|a, b| a.cmp(&b).reverse());
        }

        if self.is_straight() && self.is_flush() {
            Score::StraightFlush(self.cards[0].rank)
        } else if let (Some(quad), Some(single)) = (flipped_counts.get(&4), flipped_counts.get(&1))
        {
            Score::FourKind(quad[0], single[0])
        } else if let (Some(trip), Some(pair)) = (flipped_counts.get(&3), flipped_counts.get(&2)) {
            Score::FullHouse(trip[0], pair[0])
        } else if self.is_flush() {
            Score::Flush(
                self.cards[0].rank,
                self.cards[1].rank,
                self.cards[2].rank,
                self.cards[3].rank,
                self.cards[4].rank,
            )
        } else if self.is_straight() {
            Score::Straight(self.cards[0].rank)
        } else if let (Some(trip), Some(singles)) = (flipped_counts.get(&3), flipped_counts.get(&1))
        {
            Score::ThreeKind(trip[0], singles[0], singles[1])
        } else if let (Some(pairs), Some(singles)) =
            (flipped_counts.get(&2), flipped_counts.get(&1))
        {
            match (pairs.len(), singles.len()) {
                (2, 1) => Score::TwoPair(pairs[0], pairs[1], singles[0]),
                (1, 3) => Score::Pair(pairs[0], singles[0], singles[1], singles[2]),
                _ => unreachable!(),
            }
        } else {
            Score::Nothing(
                self.cards[0].rank,
                self.cards[1].rank,
                self.cards[2].rank,
                self.cards[3].rank,
                self.cards[4].rank,
            )
        }
    }

    fn counts(&self) -> HashMap<Rank, usize> {
        let mut counts = HashMap::new();
        for card in &self.cards {
            *counts.entry(card.rank).or_insert(0usize) += 1;
        }
        counts
    }

    fn is_straight(&self) -> bool {
        self.cards
            .iter()
            .zip(self.cards.iter().skip(1))
            .map(|(a, b)| a.rank as i32 - b.rank as i32)
            .all(|x| x == 1)
    }

    fn is_flush(&self) -> bool {
        self.cards
            .iter()
            .scan(None, |suit, card| {
                if let Some(suit) = suit {
                    Some(*suit == card.suit)
                } else {
                    *suit = Some(card.suit);
                    Some(true)
                }
            })
            .all(|x| x)
    }
}

// TODO: impl Error
#[derive(PartialEq, Eq, Clone, Copy, Debug)]
pub enum ParseHandError {
    TooFewCards,
    TooLong,
    ParseCardError(ParseCardError),
}

impl From<ParseCardError> for ParseHandError {
    fn from(error: ParseCardError) -> Self {
        ParseHandError::ParseCardError(error)
    }
}

impl FromStr for Hand {
    type Err = ParseHandError;

    fn from_str(s: &str) -> Result<Self, Self::Err> {
        let mut card_iter = s.split_whitespace().map(Card::from_str);

        let cards = [
            card_iter.next().ok_or(ParseHandError::TooFewCards)??,
            card_iter.next().ok_or(ParseHandError::TooFewCards)??,
            card_iter.next().ok_or(ParseHandError::TooFewCards)??,
            card_iter.next().ok_or(ParseHandError::TooFewCards)??,
            card_iter.next().ok_or(ParseHandError::TooFewCards)??,
        ];
        if card_iter.next().is_some() {
            Err(ParseHandError::TooLong)
        } else {
            Ok(Hand::new(cards))
        }
    }
}

impl PartialOrd for Hand {
    fn partial_cmp(&self, other: &Self) -> Option<Ordering> {
        Some(self.cmp(other))
    }
}

impl Ord for Hand {
    fn cmp(&self, other: &Self) -> Ordering {
        self.score().cmp(&other.score())
    }
}

#[derive(PartialEq, Eq, PartialOrd, Ord)]
enum Score {
    Nothing(Rank, Rank, Rank, Rank, Rank),
    Pair(Rank, Rank, Rank, Rank),
    TwoPair(Rank, Rank, Rank),
    ThreeKind(Rank, Rank, Rank),
    Straight(Rank),
    Flush(Rank, Rank, Rank, Rank, Rank),
    FullHouse(Rank, Rank),
    FourKind(Rank, Rank),
    StraightFlush(Rank),
}

#[cfg(test)]
mod test {
    use super::{
        super::{Rank::*, Suit::*, *},
        Score::*,
        *,
    };

    #[test]
    fn order() {
        assert_eq!(
            Hand::from_str("2C 4H 8D 9C JD"),
            Ok(Hand {
                cards: [
                    Card {
                        rank: Jack,
                        suit: Diamond
                    },
                    Card {
                        rank: Nine,
                        suit: Club
                    },
                    Card {
                        rank: Eight,
                        suit: Diamond
                    },
                    Card {
                        rank: Four,
                        suit: Heart
                    },
                    Card {
                        rank: Two,
                        suit: Club
                    },
                ]
            })
        );

        assert_eq!(
            Hand::from_str("2C 4H 8D 9C JD"),
            Hand::from_str("8D 9C JD 2C 4H "),
        );
    }

    #[test]
    fn parse() {
        assert_eq!(Hand::from_str(""), Err(ParseHandError::TooFewCards));
        assert_eq!(Hand::from_str("2C"), Err(ParseHandError::TooFewCards));
        assert_eq!(Hand::from_str("2C 4H"), Err(ParseHandError::TooFewCards));
        assert_eq!(Hand::from_str("2C 4H 8D"), Err(ParseHandError::TooFewCards));
        assert_eq!(
            Hand::from_str("2C 4H 8D 9C"),
            Err(ParseHandError::TooFewCards)
        );
        assert_eq!(
            Hand::from_str("2C 4H 8D 9C JD 5S"),
            Err(ParseHandError::TooLong)
        );
        assert_eq!(
            Hand::from_str("2C DH 8D 9C JD"),
            Err(ParseHandError::ParseCardError(ParseCardError::UnknownRank(
                'D'
            )))
        );
        assert_eq!(
            Hand::from_str("2C 44 8D 9C JD"),
            Err(ParseHandError::ParseCardError(ParseCardError::UnknownSuit(
                '4'
            )))
        );
        assert_eq!(
            Hand::from_str("2C 4H 8D 9C JD"),
            Ok(Hand::new([
                Card {
                    rank: Two,
                    suit: Club
                },
                Card {
                    rank: Four,
                    suit: Heart
                },
                Card {
                    rank: Eight,
                    suit: Diamond
                },
                Card {
                    rank: Nine,
                    suit: Club
                },
                Card {
                    rank: Jack,
                    suit: Diamond
                },
            ]))
        );
        assert_eq!(
            Hand::from_str("2C 4H 8D 9C JD      "),
            Ok(Hand::new([
                Card {
                    rank: Two,
                    suit: Club
                },
                Card {
                    rank: Four,
                    suit: Heart
                },
                Card {
                    rank: Eight,
                    suit: Diamond
                },
                Card {
                    rank: Nine,
                    suit: Club
                },
                Card {
                    rank: Jack,
                    suit: Diamond
                },
            ]))
        );
    }

    #[test]
    fn counts() {
        let hand = Hand::from_str("2H 3D 4C 5S 6H").unwrap();
        let counts = hand.counts();
        assert_eq!(counts[&Two], 1);
        assert_eq!(counts[&Three], 1);
        assert_eq!(counts[&Four], 1);
        assert_eq!(counts[&Five], 1);
        assert_eq!(counts[&Six], 1);

        let hand = Hand::from_str("2H 2D 2C 6S 6H").unwrap();
        let counts = hand.counts();
        assert_eq!(counts[&Two], 3);
        assert_eq!(counts[&Six], 2);
    }

    #[test]
    fn straight() {
        let hand = Hand::from_str("2H 3D 4C 5S 6H").unwrap();
        assert!(hand.is_straight());

        let hand = Hand::from_str("6H 5S 4C 3D 2H").unwrap();
        assert!(hand.is_straight());

        let hand = Hand::from_str("AH 2H 3D 4C 5S").unwrap();
        assert!(!hand.is_straight());

        let hand = Hand::from_str("TH JD QC KS AH").unwrap();
        assert!(hand.is_straight());

        let hand = Hand::from_str("3H 5D 6C 7S 8H").unwrap();
        assert!(!hand.is_straight());
    }

    #[test]
    fn flush() {
        let hand = Hand::from_str("2H 3H 7H 9H KH").unwrap();
        assert!(hand.is_flush());

        let hand = Hand::from_str("2D 3D 7D 9D KD").unwrap();
        assert!(hand.is_flush());

        let hand = Hand::from_str("2C 3C 7C 9C KC").unwrap();
        assert!(hand.is_flush());

        let hand = Hand::from_str("2S 3S 7S 9S KS").unwrap();
        assert!(hand.is_flush());

        let hand = Hand::from_str("2H 3D 7H 9H KH").unwrap();
        assert!(!hand.is_flush());

        let hand = Hand::from_str("2H 3H 7D 9H KH").unwrap();
        assert!(!hand.is_flush());

        let hand = Hand::from_str("2H 3H 7H 9D KH").unwrap();
        assert!(!hand.is_flush());

        let hand = Hand::from_str("2H 3H 7H 9H KD").unwrap();
        assert!(!hand.is_flush());

        let hand = Hand::from_str("2H 3D 7H 9H KH").unwrap();
        assert!(!hand.is_flush());

        let hand = Hand::from_str("2H 3D 7D 9H KH").unwrap();
        assert!(!hand.is_flush());

        let hand = Hand::from_str("2H 3D 7D 9D KH").unwrap();
        assert!(!hand.is_flush());

        let hand = Hand::from_str("2H 3D 7D 9D KD").unwrap();
        assert!(!hand.is_flush());

        let hand = Hand::from_str("2H 3D 7C 9S KH").unwrap();
        assert!(!hand.is_flush());
    }

    #[test]
    fn score_ord() {
        assert!(StraightFlush(Ace) > StraightFlush(King));
        assert!(StraightFlush(Six) > FourKind(King, Ace));
        assert!(StraightFlush(Six) > Nothing(Ace, King, Queen, Jack, Nine));
        assert!(Nothing(Ace, King, Queen, Jack, Nine) > Nothing(Ace, King, Queen, Jack, Eight));
        assert!(Flush(Seven, Five, Four, Three, Two) > Nothing(Ace, King, Queen, Jack, Nine));
        assert!(FullHouse(Six, Three) > FullHouse(Four, King));
    }

    #[test]
    fn hand_ord() {
        assert!(
            Hand::from_str("AH KH QH JH TH").unwrap() > Hand::from_str("9H KH QH JH TH").unwrap()
        );
        assert!(
            Hand::from_str("6H 5H 4H 3H 2H").unwrap() > Hand::from_str("KH KD KC KS AH").unwrap()
        );
        assert!(
            Hand::from_str("6H 5H 4H 3H 2H").unwrap() > Hand::from_str("AH KD QC JS 9H").unwrap()
        );
        assert!(
            Hand::from_str("AH KD QC JS 9H").unwrap() > Hand::from_str("AH KD QC JS 8H").unwrap()
        );
        assert!(
            Hand::from_str("7H 5H 4H 3H 2H").unwrap() > Hand::from_str("AH KD QC JS 9H").unwrap()
        );
        assert!(
            Hand::from_str("6H 3D 6C 6S 3H").unwrap() > Hand::from_str("KH KD 4C 4S 4H").unwrap()
        );
    }
}
