
// Tentar converter o payload de string para JSON
try {
    //let message = JSON.parse(msg.payload);

    // Criar um novo objeto com apenas as chaves desejadas
    msg.payload = 
        "Tipo de leitura: " + msg.payload.tipo_leitura + "<br>" +
        "Bike ID: " + msg.payload.bike_id + "<br>" +
        "Status: " + msg.payload.status
    ;
} catch (error) {
    // Caso ocorra um erro na conversão JSON, log o erro
    node.error("Erro ao converter o payload em JSON: " + error);
    return null;  // Parar o fluxo caso o JSON seja inválido
}

return msg;
