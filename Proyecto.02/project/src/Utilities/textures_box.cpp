#include "textures_box.h"
#include "../Managers/game/CombatManager.h"
#include "../Managers/game/PartyManager.h"
#include "../Managers/TheElementalMaze.h"
using src = Resources;

Resources::TextureId textures_box::getHeroTxt(uint number)
{
	PartyManager* c = TheElementalMaze::instance()->getPartyManager();
	std::vector<Hero*> heroes = c->getHeroes();

	heroTemplate tem = heroes[number]->getTemplate();

	uint pivot = src::_firstHeroRId_;

	Resources::TextureId id = (Resources::TextureId)(pivot + tem + 1);

	return id;
}

// hace falta un metodo como este para los enemigos y otro para las habilidades (tambien estan armas, armaduras y objetos, pero urgen menos)

Resources::TextureId textures_box::getEnemyTxt(uint number)
{
	CombatManager* c = TheElementalMaze::instance()->getCombatManager();
	std::vector<Enemy*> enemies = c->getEnemiesTeam();

	enemyTemplate tem = enemies[number]->getTemplate();

	Resources::TextureId id;

	switch (tem)
	{
	case rpgLogic::ZOMBIE:
		id = src::Zombie;
		break;
	case rpgLogic::TROLL:
		id = src::Troll;
		break;
	case rpgLogic::SKELETON:
		id = src::Skeleton;
		break;
	case rpgLogic::HELLHOUND:
		id = src::Hellhound;
		break;
	case rpgLogic::SPECTER:
		id = src::Specter;
		break;
	case rpgLogic::GOBLIN:
		id = src::Goblin;
		break;
	case rpgLogic::DEATHKNIGHT:
		id = src::DeathKnight;
		break;
	case rpgLogic::MIMIC:
		id = src::Mimic;
		break;
	case rpgLogic::PIXIE:
		id = src::Pixie;
		break;
	case rpgLogic::GHOUL:
		id = src::Ghoul;
		break;
	case rpgLogic::DRACOLICH:
		id = src::Dracolich;
		break;
	case rpgLogic::GIANTWORM:
		id = src::GiantWorm;
		break;
	case rpgLogic::BANSHEE:
		id = src::Banshee;
		break;
		//case rpgLogic::LICH:
		//	id = src::Lich;
		//	break;
		//case rpgLogic::NECROFAGO:
		//	id = src::Necrofago;
		//	break;
		//case rpgLogic::MONSTER:
		//	id = src::Monster;
		//	break;
		//case rpgLogic::DESCONOCIDO:
		//	id = src::Desconocido;
		//	break;

	default:
		id = Resources::TextureId();
		break;
	}

	return id;
}

Resources::TextureId textures_box::getItemTxt(uint number)
{
	PartyManager* c = TheElementalMaze::instance()->getPartyManager();
	std::vector<Item*> items = c->getItems();

	Resources::TextureId id;

	ItemType itemType = items[number]->getItemType();

	if (itemType == ItemType::ARMOR) {
		Armor* armor = static_cast<Armor*>(items[number]);
		rpgLogic::armorId aId = armor->getArmorId();

		switch (aId)
		{
		case rpgLogic::ACOLCHADA:
			id = src::Acolchada;
			break;
		case rpgLogic::CUEROTACHONADO:
			id = src::CueroTachonado;
			break;
		case rpgLogic::COTADEESCAMAS:
			id = src::CotaEscamas;
			break;
		case rpgLogic::CORAZA:
			id = src::Coraza;
			break;
		case rpgLogic::SEMIPLACAS:
			id = src::SemiPlacas;
			break;
		case rpgLogic::COTADEMALLA:
			id = src::CotaMalla;
			break;
		case rpgLogic::BANDAS:
			id = src::Bandas;
			break;
		case rpgLogic::PLACAS:
			id = src::Placas;
			break;
		default:
			id = Resources::TextureId();
			break;
		}
	}


	else if (itemType == ItemType::WEAPON) {
		Weapon* weapon = static_cast<Weapon*>(items[number]);
		rpgLogic::weaponId wId = weapon->getWeaponId();

		switch (wId)
		{
		case rpgLogic::DESARMADO:
			id = src::Desarmado;
			break;
		case rpgLogic::BASTON:
			id = src::Baston;
			break;
		case rpgLogic::DAGA:
			id = src::Daga;
			break;
		case rpgLogic::CLAVA:
			id = src::Clava;
			break;
		case rpgLogic::HACHAPEQUENA:
			id = src::HachaPequena;
			break;
		case rpgLogic::HOZ:
			id = src::Hoz;
			break;
		case rpgLogic::LANZA:
			id = src::Lanza;
			break;
		case rpgLogic::MARTILLOPEQUENO:
			id = src::MartilloPequeno;
			break;
		case rpgLogic::MAZA:
			id = src::Maza;
			break;
		case rpgLogic::ARCOPEQUENO:
			id = src::ArcoPequeno;
			break;
		case rpgLogic::BALLESTALIGERA:
			id = src::BallestaLigera;
			break;
		case rpgLogic::ALABARDA:
			id = src::Alabarda;
			break;
		case rpgLogic::ATARRAGA:
			id = src::Atarraga;
			break;
		case rpgLogic::ESPADACORTA:
			id = src::EspadaCorta;
			break;
		case rpgLogic::ESPADALARGA:
			id = src::EspadaLarga;
			break;
		case rpgLogic::ESPADON:
			id = src::Espadon;
			break;
		case rpgLogic::ESPADAROPERA:
			id = src::EspadaRopera;
			break;
		case rpgLogic::HACHADEBATALLA:
			id = src::HachaBatalla;
			break;
		case rpgLogic::GUJA:
			id = src::Guja;
			break;
		case rpgLogic::LATIGO:
			id = src::Latigo;
			break;
		case rpgLogic::LUCERODELALBA:
			id = src::LuceroAlba;
			break;
		case rpgLogic::MARTILLODEGUERRA:
			id = src::MartilloGuerra;
			break;
		case rpgLogic::PICA:
			id = src::Pica;
			break;
		case rpgLogic::TRIDENTE:
			id = src::Tridente;
			break;
		case rpgLogic::ARCOLARGO:
			id = src::ArcoLargo;
			break;
		case rpgLogic::BALLESTAPESADA:
			id = src::BallestaPesada;
			break;
		default:
			id = Resources::TextureId();
			break;
		}
	}

	return id;
}

Resources::TextureId textures_box::getHabilityTxt(uint hero, uint number)
{
	PartyManager* c = TheElementalMaze::instance()->getPartyManager();
	std::vector<Hero*> heroes = c->getHeroes();
	std::vector<Hability*> habilities = heroes[number]->getHabilities();

	Resources::TextureId id;

	Hability_Id idHability = habilities[number]->id();
	switch (idHability)
	{
		//-----------------------
	case LIGHTATTACK:
		id = src::LightAttack;
		break;
	case FIREBALL:
		id = src::Bola_fuego;
		break;
	case BLOODYSTRIKE:
		id = src::Bloody_strike;
		break;
	case HEALINGWORD:
		id = src::Curacion;
		break;
	case ALLYTEAMHEALEXAMPLE:
		id = src::Curacion_en_masa;
		break;
	case SELFHEALEXAMPLE:
		id = src::SelfHeal;
		break;
	case WINDBURST:
		id = src::RafagaDeViento;
		break;
	case WINDSLASH:
		id = src::Cuchilla_aerea;
		break;
	case ROCKPILLAR:
		id = src::PilarDeTierra;
		break;
	case TOXICSHADOW:
		id = src::Sombra_toxica;
		break;
	case TSUNAMI:
		id = src::Tsunami;
		break;
		//-----------------------
	case DIVINEPROTECTION:
		id = src::Proteccion_divina;
		break;
	case FLASH:
		id = src::Destello;
		break;
	case FREEZE:
		id = src::Congelar;
		break;
	case WHIRLPOOL:
		id = src::TorrenteAcuatico;
		break;
	case LIGHTBEAM:
		id = src::RayoLuminoso;
		break;
	case DARKVORTEX:
		id = src::VorticeDeOscuridad;
		break;
	case FIREARROW:
		id = src::FlechaDeFuego;
		break;
	case MEDITATE:
		id = src::Meditacion;
		break;
	case LIGHTEN:
		id = src::Aligerar;
		break;
	case STRENGTHEN:
		id = src::Fortalecer;
		break;
	case TOUGHEN:
		id = src::Endurecer;
		break;
	case BLOODTHIRST:
		id = src::SedDeSangre;
		break;
		//-------------------
	case SACRIFICE:
		id = src::Sacrificio;
		break;
	case DOUBLESHOT:
		id = src::DisparoDoble;
		break;
	case THROWINGAXES:
		id = src::HachaArrojadiza;
		break;
	case MORPH:
		id = src::Morph;
		break;
	case REVERSEMORPH:
		id = src::Morph;
		break;
	case HEAVYSTRIKE:
		id = src::GolpeDuro;
		break;
	case SMOKEARROW:
		id = src::FlechaDeHumo;
		break;
	case RAINOFDAGGERS:
		id = src::LluviaDeDagas;
		break;
	case ROCKPROJECTILES:
		id = src::ProyectilesDeRoca;
		break;
	case TRICKSHOT:
		id = src::Trickshot;
		break;
	case GLADIATORBALLAD:
		id = src::OdaDeLosGladiadores;
		break;
	case WINDSONG:
		id = src::OdaDeViento;
		break;
		//-----------------------
	case DETERMINATION:
		id = src::Determinacion;
		break;
	case _lasHabilityId_:
		break;
	default:
		break;
	}

	return id;
}
