import { serve } from "https://deno.land/std/http/server.ts";
import { getAvailablePortSync } from "https://deno.land/x/port/mod.ts";

const p = getAvailablePortSync({ port: { start: 20000, end: 65535 } });
console.log(p===undefined);
if(p !== undefined) {
    console.log(p);
    const s = serve({ hostname: "127.0.0.1", port: p });
    for await (const req of s) {
        req.respond({ body: "Response from server\n" });
    }
}
