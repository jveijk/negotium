import System.IO
import Data.Bits
import System.Random
import System.IO.Unsafe
import Data.Char

-- (Doos a) >>= f = f a

main = do 
  putStrLn "Enter the path of the file you would like to encrypt!"
  name <- getLine
  contents <- readFile name
  let cypher = take (length contents) $ randomRs ('a','z') $ unsafePerformIO newStdGen
  let encryptednr = zipWith (\x y-> xor (ord x) (ord y) ) cypher contents
  let encryptedstring = map (\x-> chr(x)) encryptednr
  --print (zipWith xor fileContent (cycle number))
  writeFile (name ++ ".encrypted") encryptedstring
  writeFile (name ++ ".key") cypher 
  putStrLn ("The file is encrypted and saved with filename: " ++ name ++ ".encrypted" ++ "\n" ++ "The key is saved with filename: " ++ name ++ ".key")
