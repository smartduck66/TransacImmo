// Lecture du fichier des transactions immobilières
// Version en Zig - OPTIMISÉE
// Compilation avec Zig : zig build-exe evalZig.zig -O ReleaseFast -fstrip
// https://ziglang.org/download/

const std = @import("std");

pub fn main() !void {
    var gpa = std.heap.GeneralPurposeAllocator(.{}){};
    defer _ = gpa.deinit();
    const allocator = gpa.allocator();

    const start_time = std.time.microTimestamp();

    const file = std.fs.cwd().openFile("./data/valeursfoncieres.txt", .{}) catch |err| {
        std.debug.print("Erreur : impossible d'ouvrir le fichier ./data/valeursfoncieres.txt\n", .{});
        return err;
    };
    defer file.close();

    var nb_records: i64 = 0;
    var total_ventes: i64 = 0;
    var MontantTransactionEnCours: i64 = 0;
    var NbTransactions: i64 = 0;

    const content = try file.readToEndAlloc(allocator, 1024 * 1024 * 1024);
    defer allocator.free(content);

    var lines = std.mem.splitSequence(u8, content, "\n");
    while (lines.next()) |line| {
        if (line.len == 0) continue;
        
        nb_records += 1;

        // Extraction directe du champ 10 (prix)
        var field_index: i32 = 0;
        var pos: usize = 0;

        // Parcourir jusqu'au 10ème séparateur
        while (field_index < 10 and pos < line.len) {
            if (std.mem.indexOfScalarPos(u8, line, pos, '|')) |next_pos| {
                pos = next_pos + 1;
                field_index += 1;
            } else {
                break;
            }
        }

        // Extraire le champ 10 (prix)
        if (field_index == 10 and pos < line.len) {
            // Chercher le prochain séparateur ou la fin de ligne
            const next_delimiter = std.mem.indexOfScalarPos(u8, line, pos, '|') orelse line.len;

            // Chercher la virgule (décimale)
            const comma_pos = std.mem.indexOfScalarPos(u8, line, pos, ',');
            const end_pos = if (comma_pos) |cp| (if (cp < next_delimiter) cp else next_delimiter) else next_delimiter;

            if (end_pos > pos) {
                const price_str = line[pos..end_pos];
                if (std.fmt.parseInt(i64, price_str, 10)) |price| {
                    // On vérifie si le prix est différent du montant de la transaction en cours : si c'est le cas,
                    // on a changé de transaction et on peut donc ajouter le montant de la transaction précédente au total
                    if (price != MontantTransactionEnCours) {
                        total_ventes += MontantTransactionEnCours;
                        MontantTransactionEnCours = price;
                        NbTransactions += 1;
                    }

                } else |_| {
                    // Ignorer les valeurs invalides
                }
            }
        }
    }

    const end_time = std.time.microTimestamp();
    const duration_ms = @divTrunc(@as(i64, @intCast(end_time - start_time)), 1000);

    const billions = @as(f64, @floatFromInt(total_ventes)) / 1_000_000_000.0;

    std.debug.print("Nb d'enregistrements du fichier : {}\n", .{nb_records});
    std.debug.print("Nb de transactions immobilieres : {}\n", .{NbTransactions});
    std.debug.print("Montant total des ventes        : {d:.0} milliards d'euros\n", .{billions});
    std.debug.print("Temps d'execution en Zig        : {} millisecondes\n", .{duration_ms});
}
