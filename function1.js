
try {
    // Tentar converter o payload de string para JSON
    //let parsedMessage = JSON.parse(msg.payload);

    // Recuperar dados salvos ou iniciar um novo array
    let tableData = flow.get("savedData") || [];

    // Adicionar nova entrada no início do array
    tableData.unshift({
        "tipo_leitura": msg.payload.tipo_leitura,
        "bike_id": msg.payload.bike_id,
        "status": msg.payload.status
    });

    // Atualizar o fluxo com os dados salvos
    flow.set("savedData", tableData);

    // Enviar o conteúdo atualizado da tabela como payload
    msg.payload = tableData;

} catch (error) {
    // Logar o erro para entender o que deu errado
    node.error("Erro ao converter o payload em JSON: " + error);
    return null;  // Parar o fluxo caso o JSON seja inválido
}

return msg;
