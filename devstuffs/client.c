#include <stdio.h>
#include <hiredis/hiredis.h>

int main() {
    redisContext *c = redisConnect("127.0.0.1", 6379);
    if (c == NULL || c->err) {
        if (c) {
            printf("Connection error: %s\n", c->errstr);
            redisFree(c);
        } else {
            printf("Connection error: can't allocate redis context\n");
        }
        return 1;
    }

    // Set a key-value pair
    redisReply *reply = redisCommand(c, "SET %s %s", "key", "value");
    printf("SET: %s\n", reply->str);
    freeReplyObject(reply);

    // Get the value of the key
    reply = redisCommand(c, "GET %s", "key");
    printf("GET: %s\n", reply->str);
    freeReplyObject(reply);

    // Free Redis context
    redisFree(c);
    return 0;
}
