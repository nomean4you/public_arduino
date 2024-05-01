//TickerNames.h


#ifndef TICKER_NAMES_H
#define TICKER_NAMES_H

struct TickerInfo {
    const char* symbol;      // 티커 심볼
    const char* koreanName;  // 티커 한글명
    const char* englishName; // 티커 영문명
};

// 그룹 1
const TickerInfo group1[] = {
    {"ADA", "에이다", "Ada"},
    {"AERGO", "아르고", "Aergo"},
    {"AKT", "아카시네트워크", "Akash Network"},
    {"ALGO", "알고랜드", "Algorand"},
    {"ANKR", "앵커", "Ankr"},
    {"APT", "앱토스", "Aptos"},
    {"ARB", "아비트럼", "Arbitrum"},
    {"ARK", "아크", "Ark"},
    {"ASTR", "아스타", "Astar"},
    {"AVAX", "아발란체", "Avalanche"},
    {"AXS", "엑시인피니티", "Axie Infinity"},
    {"BAT", "베이직어텐션토큰", "Basic Attention Token"},
    {"BCH", "비트코인캐시", "Bitcoin Cash"},
    {"BLUR", "블러", "Blur"},
    {"BSV", "비트코인에스브이", "Bitcoin SV"},
    {"BTC", "비트코인", "Bitcoin"},
    {"BTG", "비트코인골드", "Bitcoin Gold"},
    {"BTT", "비트토렌트", "BitTorrent"},
    {"CELO", "셀로", "Celo"},
    {"CHZ", "칠리즈", "Chiliz"},
    {"CRE", "캐리프로토콜", "Carry Protocol"},
    {"CTC", "크레딧코인", "Creditcoin"},
    {"CVC", "시빅", "Civic"},
    {"DOGE", "도지코인", "Dogecoin"},
    {"DOT", "폴카닷", "Polkadot"}
};

// 그룹 2
const TickerInfo group2[] = {
    {"ELF", "엘프", "aelf"},
    {"EOS", "이오스", "EOS"},
    {"ETC", "이더리움클래식", "Ethereum Classic"},
    {"ETH", "이더리움", "Ethereum"},
    {"FCT2", "피르마체인", "FirmaChain"},
    {"FLOW", "플로우", "Flow"},
    {"GAS", "가스", "Gas"},
    {"GLM", "골렘", "Golem"},
    {"GMT", "스테픈", "STEPN"},
    {"GRT", "더그래프", "The Graph"},
    {"HBAR", "헤데라", "Hedera Hashgraph"},
    {"HIFI", "하이파이", "Hifi Finance"},
    {"HPO", "히포크랏", "Hypocrit"},
    {"ID", "스페이스아이디", "Space ID"},
    {"IQ", "아이큐", "Everipedia"},
    {"KAVA", "카바", "Kava"},
    {"KNC", "카이버네트워크", "Kyber Network"},
    {"LINK", "체인링크", "Chainlink"},
    {"LOOM", "룸네트워크", "Loom Network"},
    {"LSK", "리스크", "Lisk"},
    {"MANA", "디센트럴랜드", "Decentraland"},
    {"MASK", "마스크네트워크", "Mask Network"},
    {"MATIC", "폴리곤", "Polygon"},
    {"MBL", "무비블록", "MovieBloc"},
    {"META", "메타디움", "Metadium"}
};

// 그룹 3
const TickerInfo group3[] = {
    {"MINA", "미나", "Mina"},
    {"MNT", "맨틀", "Mantle"},
    {"MOC", "모스코인", "Moss Coin"},
    {"MTL", "메탈", "Metal"},
    {"MVL", "엠블", "MVL"},
    {"NEAR", "니어프로토콜", "NEAR Protocol"},
    {"NEO", "네오", "Neo"},
    {"ONG", "온톨로지가스", "Ontology Gas"},
    {"ONT", "온톨로지", "Ontology"},
    {"ORBS", "오브스", "Orbs"},
    {"POLYX", "폴리매쉬", "Polymath"},
    {"POWR", "파워렛저", "Power Ledger"},
    {"PUNDIX", "펀디엑스", "Pundi X"},
    {"PYTH", "피스네트워크", "Pyth Network"},
    {"QTUM", "퀀텀", "Qtum"},
    {"SAND", "샌드박스", "The Sandbox"},
    {"SC", "시아코인", "Siacoin"},
    {"SEI", "세이", "Sei"},
    {"SHIB", "시바이누", "Shiba Inu"},
    {"SOL", "솔라나", "Solana"},
    {"STEEM", "스팀", "Steem"},
    {"STMX", "스톰엑스", "StormX"},
    {"STORJ", "스토리지", "Storj"},
    {"STPT", "에스티피", "STP Network"},
    {"STRAX", "스트라티스", "Stratis"}
};

// 그룹 4
const TickerInfo group4[] = {
    {"STX", "스택스", "Stacks"},
    {"SUI", "수이", "Sui"},
    {"SXP", "솔라", "Swipe"},
    {"T", "쓰레스홀드", "Threshold"},
    {"THETA", "쎄타토큰", "Theta"},
    {"TRX", "트론", "TRON"},
    {"UPP", "센티넬프로토콜", "Sentinel Protocol"},
    {"VET", "비체인", "VeChain"},
    {"WAVES", "웨이브", "Waves"},
    {"WAXP", "왁스", "WAX"},
    {"XEC", "이캐시", "eCash"},
    {"XEM", "넴", "NEM"},
    {"XLM", "스텔라루멘", "Stellar"},
    {"XRP", "리플", "Ripple"},
    {"ZIL", "질리카", "Zilliqa"},
    {"ZRX", "제로엑스", "0x"}
};

#endif
