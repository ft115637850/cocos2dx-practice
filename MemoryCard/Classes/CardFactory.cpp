#include "ui/CocosGUI.h"
#include "CardFactory.h"
#include "Card.h"

ICard * CardFactory::createCard(int backId, unsigned int number)
{
	const int cardSize = 256;
	if (backId < 0 || backId >= 8) {
		backId = 0;
	}

	// Create back image
	int x = (backId % 2)*cardSize;
	int y = (backId / 2)*cardSize;
	auto backImage = Sprite::create("card_back.png", Rect(x, y, cardSize, cardSize));

	// Create front image
	auto frontImage = Node::create();
	frontImage->setContentSize(Size(cardSize, cardSize));
	frontImage->addChild(Sprite::create("card_front.png"));
	auto numberText = ui::TextAtlas::create(StringUtils::format("%d", number), "card_number.png", 140, 140, "0");
	frontImage->addChild(numberText);

	// Create card data
	CardData data = {};
	data.number = number;

	// create card
	auto card = Card::create();
	card->setBackImage(backImage);
	card->setFrontImage(frontImage);
	card->setCardData(data);
	card->setContentSize(backImage->getContentSize());
	return card;
}
