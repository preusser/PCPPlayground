module SolvePCP where

--
-- SolvePCP -- Solve a given instance of PCP
--

import Control.Arrow
import Data.List (isPrefixOf)
import Data.Maybe (fromMaybe)
import Data.Tree
import System.Environment (getArgs, getProgName)


-- define PCP instances
type WordPair = (String, String)
type PCPInstance = [WordPair]

instanceOne :: PCPInstance
instanceOne = [("a",     "aaa"),
               ("abaaa", "ab"),
               ("ab",    "b")]

instanceTwo :: PCPInstance
instanceTwo = [("bba", "b"),
               ("ba",  "baa"),
               ("ba",  "aba"),
               ("ab",  "bba")]

-- size of instance
sizeOfInstance :: PCPInstance -> Int
sizeOfInstance = length

-- nth element of instance
nthOfInstance :: PCPInstance -> Int -> WordPair
nthOfInstance p i = p !! (i - 1)

-- reverse instance
-- revInstance :: PCPInstance -> PCPInstance
-- revInstance = map $ join (***) reverse
-- revInstance = map $ \ (x, y) -> (reverse x, reverse y)

-- get word pair from list of indeces
getWords :: PCPInstance -> [Int] -> WordPair
getWords p = (concatMap fst &&& concatMap snd) . map (nthOfInstance p)



data PruneValue = Solution
                | ExtensionPossible
                | NoExtensionPossible
                

check :: PCPInstance -> [Int] -> PruneValue
check _ [] = ExtensionPossible
check p xs
  | u == v                               = Solution
  | u `isPrefixOf` v || v `isPrefixOf` u = ExtensionPossible
  | otherwise                            = NoExtensionPossible
  where
    (u, v) = getWords p xs



createSearchTree :: Int -> Tree [Int]
createSearchTree br = unfoldTree (\ xs -> (xs, [xs ++ [i] | i <- [1..br]])) []

pruneSearchTree :: ([Int] -> PruneValue) -> Tree [Int] -> Tree ([Int], Bool)
pruneSearchTree f (Node xs ts) =
  case f xs of
    Solution            -> Node (xs, True)  $ map (pruneSearchTree f) ts
    ExtensionPossible   -> Node (xs, False) $ map (pruneSearchTree f) ts
    NoExtensionPossible -> Node (xs, False) []


search :: Tree ([Int], Bool) -> Maybe [Int]
search = go . flatten
  where
    go :: [([Int], Bool)] -> Maybe [Int]
    go []                = Nothing
    go ((xs, True) : _)  = Just xs
    go (_          : ys) = go ys
    
limitTree :: Int -> Tree ([Int], Bool) -> Tree ([Int], Bool)
limitTree 0 (Node l _)  = Node l []
limitTree n (Node l ts) = Node l $ map (limitTree (n-1)) ts


searchMaxLevel :: Int -> Tree ([Int], Bool) -> [Int]
searchMaxLevel i t = fromMaybe (searchMaxLevel (i + 1) t) (search $ limitTree i t)

searchLevels :: Tree ([Int], Bool) -> [Int]
searchLevels = go . concat . levels
  where
    go :: [([Int], Bool)] -> [Int]
    go ((xs, True) : _)  = xs
    go (_          : ys) = go ys


startSearch :: PCPInstance -> [Int]
-- startSearch p = searchMaxLevel 1 $ pruneSearchTree (check p) $ createSearchTree $ sizeOfInstance p
startSearch p = searchLevels $ pruneSearchTree (check p) $ createSearchTree $ sizeOfInstance p

showSolution :: [Int] -> IO ()
showSolution xs = mapM_ putStrLn
  [ "Solution: " ++ show xs ++ "."
  , "Length of solution: " ++ show (length xs) ++ "."
  ]

main :: IO ()
main = do args <- getArgs
          case args of
            ["1"] -> showSolution $ startSearch instanceOne
            ["2"] -> showSolution $ startSearch instanceTwo
            _     -> printHelp

printHelp :: IO ()
printHelp = getProgName >>= \ progName -> mapM_ putStrLn
  [ progName ++ " <CMD>"
  , "  where <CMD> is one of"
  , "    1: Solve PCP instance P_1 := " ++ show instanceOne ++ "."
  , "    2: Solve PCP instance P_2 := " ++ show instanceTwo ++ "."
  ]



{-

  Written by Marcel Lippmann <marcel.lippmann@tu-dresden.de>.
  Copyright (c) 2015 by Marcel Lippmann.  All rights reserved.

-}
