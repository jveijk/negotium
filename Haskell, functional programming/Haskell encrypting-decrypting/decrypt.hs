import System.IO
import Data.Bits
import Data.Char

-- (Doos a) >>= f = f a

main = do 
  putStrLn "Enter the path of the file you would like to decrypt!"
  name <- getLine
  contents <- readFile name
  putStrLn "Now enter the path of the encryption key"
  nameKey <- getLine
  keyContent <- readFile nameKey

  let decryptednr = zipWith (\x y-> xor (ord x) (ord y) ) contents keyContent
  let decryptedstring = map (\x-> chr(x)) decryptednr
  --print (zipWith xor fileContent (cycle number))
  writeFile ("decryptedFile") decryptedstring
  putStrLn "The file is decrypted and saved with filename: decryptedfile"
