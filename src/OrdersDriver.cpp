#define ORDERS_DRIVER


#ifdef ORDERS_DRIVER
#include <string>

#include "Map.h"
#include "Orders.h"
#include "Player.h"

int main() {
  // Create some players and territories to carry the tests on
  Player *player = new Player();
  Player *opponent = new Player();
  Territory *playerTerritory =
      new Territory(&std::string("Player's territory"));
  Territory *opponentTerritory =
      new Territory(&std::string("Opponent's territory"));
  playerTerritory->SetPlayer(player);
  opponentTerritory->SetPlayer(opponent);
  playerTerritory->AddNeighbor(opponentTerritory);
  opponentTerritory->AddNeighbor(playerTerritory);

  // Test the orders
  Order *deploy = new Deploy(player, playerTerritory);
  Order *advance = new Advance(player, playerTerritory, opponentTerritory);
  Order *bomb = new Bomb(player, playerTerritory, opponentTerritory);
  Order *blockade = new Blockade(player, playerTerritory);
  Order *negotiate = new Negotiate(player, opponent);
  Order *airlift = new Airlift(player, playerTerritory, opponentTerritory);

  std::cout << "Deploy is valid: " << deploy->validate() << std::endl;
  deploy->execute();
  std::cout << "Advance is valid: " << advance->validate() << std::endl;
  advance->execute();
  std::cout << "Bomb is valid: " << bomb->validate() << std::endl;
  bomb->execute();
  std::cout << "Blockade is valid: " << blockade->validate() << std::endl;
  blockade->execute();
  std::cout << "Negotiate is valid: " << negotiate->validate() << std::endl;
  negotiate->execute();
  std::cout << "Airlift is valid: " << airlift->validate() << std::endl;
  airlift->execute();

  // Test the orders list
  OrdersList *ordersList = new OrdersList();
  ordersList->queue(deploy);
  ordersList->queue(advance);
  ordersList->queue(bomb);
  ordersList->queue(blockade);
  ordersList->queue(negotiate);
  ordersList->queue(airlift);

  ordersList->move(1, 4);
  ordersList->move(3, 5);
  ordersList->move(2, 1);
  ordersList->remove(2);
  ordersList->remove(5);

  delete player;
  delete opponent;
  delete playerTerritory;
  delete opponentTerritory;
  delete deploy;
  delete advance;
  delete bomb;
  delete blockade;
  delete negotiate;
  delete airlift;
  delete ordersList;
  return 0;
};
#endif
