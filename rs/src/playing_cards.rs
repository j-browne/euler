use std::str::FromStr;

pub mod poker;

#[derive(PartialEq, Eq, PartialOrd, Ord, Clone, Copy, Debug, Hash)]
pub enum Rank {
    Two = 2,
    Three,
    Four,
    Five,
    Six,
    Seven,
    Eight,
    Nine,
    Ten,
    Jack,
    Queen,
    King,
    Ace,
}

#[derive(PartialEq, Eq, Clone, Copy, Debug, Hash)]
pub enum Suit {
    Heart,
    Diamond,
    Club,
    Spade,
}

#[derive(PartialEq, Eq, Clone, Debug, Hash)]
pub struct Card {
    pub rank: Rank,
    pub suit: Suit,
}

// TODO: impl Error
#[derive(PartialEq, Eq, Clone, Copy, Debug)]
pub enum ParseCardError {
    UnknownRank(char),
    NoRank,
    UnknownSuit(char),
    NoSuit,
    TooLong,
}

impl FromStr for Card {
    type Err = ParseCardError;

    fn from_str(s: &str) -> Result<Self, Self::Err> {
        let mut char_iter = s.chars();
        let rank = match char_iter.next() {
            Some('2') => Rank::Two,
            Some('3') => Rank::Three,
            Some('4') => Rank::Four,
            Some('5') => Rank::Five,
            Some('6') => Rank::Six,
            Some('7') => Rank::Seven,
            Some('8') => Rank::Eight,
            Some('9') => Rank::Nine,
            Some('T') => Rank::Ten,
            Some('J') => Rank::Jack,
            Some('Q') => Rank::Queen,
            Some('K') => Rank::King,
            Some('A') => Rank::Ace,
            Some(c) => Err(ParseCardError::UnknownRank(c))?,
            None => Err(ParseCardError::NoRank)?,
        };
        let suit = match char_iter.next() {
            Some('H') => Suit::Heart,
            Some('D') => Suit::Diamond,
            Some('C') => Suit::Club,
            Some('S') => Suit::Spade,
            Some(c) => Err(ParseCardError::UnknownSuit(c))?,
            None => Err(ParseCardError::NoSuit)?,
        };
        if char_iter.next().is_some() {
            Err(ParseCardError::TooLong)
        } else {
            Ok(Card { rank, suit })
        }
    }
}

#[cfg(test)]
mod test {
    use super::{Rank::*, Suit::*, *};

    #[test]
    fn parse() {
        assert_eq!("".parse::<Card>(), Err(ParseCardError::NoRank));
        assert_eq!("4".parse::<Card>(), Err(ParseCardError::NoSuit));
        assert_eq!("H4".parse::<Card>(), Err(ParseCardError::UnknownRank('H')));
        assert_eq!("44".parse::<Card>(), Err(ParseCardError::UnknownSuit('4')));
        assert_eq!("4HH".parse::<Card>(), Err(ParseCardError::TooLong));
        assert_eq!("4H ".parse::<Card>(), Err(ParseCardError::TooLong));
        assert_eq!(
            "4H".parse::<Card>(),
            Ok(Card {
                rank: Four,
                suit: Heart
            })
        );
    }
}
