{-|Func. Prog. 2
Opdracht 1
datatypes "GeoFig"|-}
import Data.List
data Kleur = Rood|Blauw|Geel
    deriving (Show, Eq)

data GeoFig = Vierkant { lengte::Float, kleur::Kleur }|Rechthoek {lengte::Float, breedte::Float, kleur::Kleur}|Driehoek {lengte::Float, kleur::Kleur}|Cirkel {lengte::Float, kleur::Kleur}
    deriving Show

geoFigures = [Vierkant 10 Blauw, Driehoek 12 Geel, Cirkel 4 Blauw, Rechthoek 23 12 Rood]

geoCalcOpp :: GeoFig -> Float
geoCalcOpp (Vierkant x _) = x*x
geoCalcOpp (Rechthoek x y _) = x*y
geoCalcOpp (Driehoek x _) = x*x/2
geoCalcOpp (Cirkel x _) = pi*x*x

geoCalcOmt :: GeoFig -> Float
geoCalcOmt (Vierkant x _) = x*4
geoCalcOmt (Rechthoek x y _) = x+y*2
geoCalcOmt (Driehoek x _) = x*3
geoCalcOmt (Cirkel x _) = pi*(2*x)

-- deelopdracht 6 lijst filteren
isVierkant :: GeoFig -> Bool
isVierkant (Vierkant _ _) = True
isVierkant _ = False

isDriehoek :: GeoFig -> Bool
isDriehoek (Driehoek _ _) = True
isDriehoek _ = False

isCirkel :: GeoFig->Bool
isCirkel (Cirkel _ _) = True
isCirkel _ = False

isRechthoek :: GeoFig->Bool
isRechthoek (Rechthoek _ _ _) = True
isRechthoek _ = False

geefVierkanten :: [GeoFig] -> [GeoFig]
geefVierkanten l = filter isVierkant l

geefDriehoeken :: [GeoFig] -> [GeoFig]
geefDriehoeken l = filter isDriehoek l

geefCirkels :: [GeoFig] -> [GeoFig]
geefCirkels l = filter isCirkel l

geefRechthoeken :: [GeoFig] -> [GeoFig]
geefRechthoeken l = filter isRechthoek l
-- Deelopdracht 6 end

-- Start Deelopdracht 7
getFigurenMetKleur::Kleur->[GeoFig]->[GeoFig]
getFigurenMetKleur k geo = filter (\x->  kleur x == k ) geo

-- Deelopdracht 7 end

-- Deelopdracht 8 Begin

geefGrootsteOpp :: [GeoFig] -> GeoFig
geefGrootsteOpp x = last(sortOn (geoCalcOpp) (x))
--n, met n+1, herhalen tot eind van lijst, vergelijken en hoogste houden
-- Deelopdracht 8 end

-- Deelopdracht 9 begin
addGeoFig :: GeoFig -> [GeoFig] -> [GeoFig]
addGeoFig a l  = l ++ [a]
-- Deelopdracht 9 end

-- Deelopdracht 10 begin
push :: [GeoFig] -> [Float]
push list = map (\x-> geoCalcOpp x) list
-- Deelopdracht 10 end
